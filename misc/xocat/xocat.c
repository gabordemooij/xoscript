#define _XOPEN_SOURCE 700
#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "bearssl.h"

static void xocat_helper_errexit(const char *m) { fprintf(stderr, "xocat: %s%s%s\n", m, errno ? ": " : "", errno ? strerror(errno) : ""); exit(1); }
static void xocat_helper_nonblock(int fd) { fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK); }

typedef struct { unsigned char *data; size_t len; } buf_t;
typedef struct { char name[128]; buf_t der; } pem_t;

static void xocat_helper_append2buf(void *ctx, const void *data, size_t len) {
	buf_t *b = ctx;
	if (!(b->data = realloc(b->data, b->len + len))) xocat_helper_errexit("out of memory");
	memcpy(b->data + b->len, data, len);
	b->len += len;
}

/* appends all PEM objects of a file to *objs, returns new count */
static int xocat_certificate(const char *path, pem_t **objs, int n) {
	br_pem_decoder_context pc;
	buf_t file = {0};
	unsigned char tmp[4096];
	size_t r, off = 0;
	FILE *f;
	if (!path || !(f = fopen(path, "rb"))) {
		fprintf(stderr, "xocat: cannot open %s\n", path ? path : "(missing env var)");
		exit(1);
	}
	while ((r = fread(tmp, 1, sizeof tmp, f)) > 0) xocat_helper_append2buf(&file, tmp, r);
	if (ferror(f)) xocat_helper_errexit("cannot read PEM file");
	fclose(f);
	xocat_helper_append2buf(&file, "\n", 1);
	br_pem_decoder_init(&pc);
	while (off < file.len) {
		off += br_pem_decoder_push(&pc, file.data + off, file.len - off);
		switch (br_pem_decoder_event(&pc)) {
		case BR_PEM_BEGIN_OBJ:
			if (!(*objs = realloc(*objs, (n + 1) * sizeof(pem_t)))) xocat_helper_errexit("out of memory");
			memset(&(*objs)[n], 0, sizeof(pem_t));
			snprintf((*objs)[n].name, sizeof (*objs)[n].name, "%s", br_pem_decoder_name(&pc));
			br_pem_decoder_setdest(&pc, xocat_helper_append2buf, &(*objs)[n].der);
			break;
		case BR_PEM_END_OBJ:
			n++;
			break;
		case BR_PEM_ERROR:
			fprintf(stderr, "xocat: invalid PEM in %s\n", path);
			exit(1);
		}
	}
	free(file.data);
	return n;
}

static void* xocat_helper_alloc_copy(const void *p, size_t len) {
	void* d = malloc(len ? len : 1);
	if (!d) xocat_helper_errexit("out of memory");
	memcpy(d, p, len);
	return d;
}

static unsigned char iobuf[BR_SSL_BUFSIZE_BIDI];
static int sock = -1;
static volatile sig_atomic_t winch = 1;             // send window size at start too
static int master = -1;                             // server
static pid_t child = -1;
static char **prog;
static unsigned char hdr[3], ctrl[8];
static size_t hlen, rem, clen;
static int sent_hello = 0, in_eof = 0; //client
static struct termios saved_tio;

static void xocat_helper_winsize(struct winsize *ws) {
	memset(ws, 0, sizeof *ws);
	if (ioctl(0, TIOCGWINSZ, ws) < 0 || ws->ws_row == 0) { ws->ws_row = 24; ws->ws_col = 80; }
}

// server
static void xocat_new_program_instance(unsigned rows, unsigned cols) {
	struct winsize ws = {0};
	int slave;
	if ((master = posix_openpt(O_RDWR | O_NOCTTY)) < 0 || grantpt(master) < 0 || unlockpt(master) < 0)
		xocat_helper_errexit("cannot create pty");
	if ((slave = open(ptsname(master), O_RDWR | O_NOCTTY)) < 0) xocat_helper_errexit("cannot open pty");
	ws.ws_row = rows; ws.ws_col = cols;
	ioctl(slave, TIOCSWINSZ, &ws);
	if ((child = fork()) < 0) xocat_helper_errexit("fork");
	if (child == 0) {
		if (setsid()<0 || ioctl(slave,TIOCSCTTY,0)<0 || dup2(slave,0)<0 || dup2(slave,1)<0) _exit(127); //not for stderr, may expose sensitive data
		close(slave); close(master); close(sock);
		signal(SIGPIPE, SIG_DFL); signal(SIGCHLD, SIG_DFL);
		execvp(prog[0], prog);
		fprintf(stderr, "xocat: cannot run %s: %s\n", prog[0], strerror(errno));
		_exit(127);
	}
	close(slave);
	xocat_helper_nonblock(master);
}

static void xocat_frame_done(void) {
	unsigned char t = hdr[0];
	hlen = 0;
	if (t == 'H' && clen >= 4 && child < 0) {
		alarm(0);
		xocat_new_program_instance((ctrl[0] << 8) | ctrl[1], (ctrl[2] << 8) | ctrl[3]);
	} else if (t == 'W' && clen >= 4 && master >= 0) {
		struct winsize ws = {0};
		ws.ws_row = (ctrl[0] << 8) | ctrl[1];
		ws.ws_col = (ctrl[2] << 8) | ctrl[3];
		ioctl(master, TIOCSWINSZ, &ws);
	} else if (t == 'E' && master >= 0) { // E simulates Ctrl-D, pipe-mode not supported, agent has to use wrapper
		char eot = 4;
		(void)!write(master, &eot, 1);
	}
}

// server: parse frames from the client, returns bytes consumed; 0 means the program's stdin is full (wait for POLLOUT)
static size_t xocat_server_deliver(unsigned char *b, size_t len) {
	size_t i = 0;
	while (i < len) {
		if (hlen < 3) {
			hdr[hlen++] = b[i++];
			if (hlen == 3) {
				rem = ((size_t)hdr[1] << 8) | hdr[2];
				clen = 0;
				if (rem == 0) xocat_frame_done();
			}
		} else if (hdr[0] == 'D') {
			size_t n = rem < len - i ? rem : len - i;
			ssize_t w = master >= 0 ? write(master, b + i, n) : (ssize_t)n;
			if (w < 0 && (errno == EAGAIN || errno == EINTR)) return i;
			if (w < 0) w = n; // program closed stdin: drop
			i += w; rem -= w;
			if (rem == 0) xocat_frame_done();
		} else {
			if (clen < sizeof ctrl) ctrl[clen++] = b[i];
			i++;
			if (--rem == 0) xocat_frame_done();
		}
	}
	return i;
}

// client helpers
static void xocat_helper_restore_tty(void) { tcsetattr(0, TCSAFLUSH, &saved_tio); }
static void xocat_helper_on_winch(int s) { (void)s; winch = 1; }
static void xocat_helper_put_frame(unsigned char *b, int type, size_t len) { b[0] = type; b[1] = len >> 8; b[2] = len & 255; }

// client: produce frames into the send buffer, returns bytes written
static size_t xocat_client_produce(unsigned char *b, size_t len, int readable) {
	struct winsize ws;
	ssize_t n;
	if (len < 16) return 0;
	if (!sent_hello) {
		xocat_helper_winsize(&ws);
		xocat_helper_put_frame(b, 'H', 4);
		b[3] = ws.ws_row >> 8; b[4] = ws.ws_row & 255;
		b[5] = ws.ws_col >> 8; b[6] = ws.ws_col & 255;
		sent_hello = 1; winch = 0;
		return 7;
	}
	if (winch) {
		winch = 0;
		xocat_helper_winsize(&ws);
		xocat_helper_put_frame(b, 'W', 4);
		b[3] = ws.ws_row >> 8; b[4] = ws.ws_row & 255;
		b[5] = ws.ws_col >> 8; b[6] = ws.ws_col & 255;
		return 7;
	}
	if (!readable || in_eof) return 0;
	n = read(0, b + 3, len - 3 < 65535 ? len - 3 : 65535);
	if (n < 0) return 0;
	if (n == 0) { in_eof = 1; xocat_helper_put_frame(b, 'E', 0); return 3; }
	xocat_helper_put_frame(b, 'D', n);
	return n + 3;
}

static int xocat_write_all(int fd, const unsigned char *b, size_t len) {
	while (len > 0) {
		ssize_t w = write(fd, b, len);
		if (w < 0 && errno == EINTR) continue;
		if (w <= 0) return -1;
		b += w; len -= w;
	}
	return 0;
}

static int xocat_pump(br_ssl_engine_context *eng, int server) {
	int out_closed = 0;
	for (;;) {
		unsigned st = br_ssl_engine_current_state(eng);
		struct pollfd pf[3];
		int np = 1, ip = -1;
		unsigned char *b;
		size_t len;
		ssize_t n;
		if (st & BR_SSL_CLOSED) return br_ssl_engine_last_error(eng);
		if (st & BR_SSL_RECVAPP) {
			b = br_ssl_engine_recvapp_buf(eng, &len);
			if (server) n = xocat_server_deliver(b, len);
			else n = xocat_write_all(1, b, len) < 0 ? 0 : (ssize_t)len;
			if (!server && n == 0) return -1;
			if (n > 0) { br_ssl_engine_recvapp_ack(eng, n); continue; }
		}
		if (!server && (st & BR_SSL_SENDAPP)) {
			b = br_ssl_engine_sendapp_buf(eng, &len);
			if ((n = xocat_client_produce(b, len, 0)) > 0) {
				br_ssl_engine_sendapp_ack(eng, n);
				br_ssl_engine_flush(eng, 0);
				continue;
			}
		}
		pf[0].fd = sock;
		pf[0].events = ((st & BR_SSL_SENDREC) ? POLLOUT : 0) | ((st & BR_SSL_RECVREC) ? POLLIN : 0);
		if ((st & BR_SSL_RECVAPP) && server && master >= 0) {
			pf[np].fd = master; pf[np++].events = POLLOUT;
		}
		if ((st & BR_SSL_SENDAPP) && !out_closed) {
			int fd = server ? master : (in_eof ? -1 : 0);
			if (fd >= 0) { ip = np; pf[np].fd = fd; pf[np++].events = POLLIN; }
		}
		if (poll(pf, np, -1) < 0) {
			if (errno == EINTR) continue;
			return -1;
		}
		if (pf[0].revents & (POLLIN | POLLHUP | POLLERR)) {
			b = br_ssl_engine_recvrec_buf(eng, &len);
			n = read(sock, b, len);
			if (n == 0 || (n < 0 && errno != EAGAIN && errno != EINTR)) return -1;
			if (n > 0) br_ssl_engine_recvrec_ack(eng, n);
			continue;
		}
		if (pf[0].revents & POLLOUT) {
			b = br_ssl_engine_sendrec_buf(eng, &len);
			n = write(sock, b, len);
			if (n < 0 && errno != EAGAIN && errno != EINTR) return -1;
			if (n > 0) br_ssl_engine_sendrec_ack(eng, n);
			continue;
		}
		if (ip >= 0 && (pf[ip].revents & (POLLIN | POLLHUP | POLLERR))) {
			b = br_ssl_engine_sendapp_buf(eng, &len);
			if (server) {
				n = read(master, b, len);
				if (n < 0 && (errno == EAGAIN || errno == EINTR)) continue;
				if (n <= 0) { out_closed = 1; br_ssl_engine_close(eng); continue; }
			} else {
				n = xocat_client_produce(b, len, 1);
			}
			if (n > 0) {
				br_ssl_engine_sendapp_ack(eng, n);
				br_ssl_engine_flush(eng, 0);
			}
		}
	}
}

static int xocat_server_main(char **argv) {
	static br_skey_decoder_context skd;
	static br_ssl_server_context sc;
	br_x509_certificate chain[16];
	struct addrinfo hints, *ai, *a;
	struct pollfd lfd[16];
	pem_t *objs = NULL;
	const char *port = getenv("PORT"), *cert = getenv("XOCAT_CERT"), *key = getenv("XOCAT_KEY");
	int n, i, nc = 0, nl = 0, have_key = 0, one = 1, err;
	prog = argv;
	if (!port) { errno = 0; xocat_helper_errexit("set PORT"); }
	n = xocat_certificate(cert, &objs, 0);
	if (key && strcmp(key, cert)) n = xocat_certificate(key, &objs, n);
	for (i = 0; i < n; i++) {
		if (strstr(objs[i].name, "CERTIFICATE")) {
			if (nc >= 16) { errno = 0; xocat_helper_errexit("too many certificates (maximum 16)"); }
			chain[nc].data = objs[i].der.data;
			chain[nc++].data_len = objs[i].der.len;
		} else if (strstr(objs[i].name, "PRIVATE KEY") && !have_key) {
			br_skey_decoder_init(&skd);
			br_skey_decoder_push(&skd, objs[i].der.data, objs[i].der.len);
			have_key = br_skey_decoder_last_error(&skd) == 0
				&& br_skey_decoder_key_type(&skd) == BR_KEYTYPE_EC;
		}
	}
	errno = 0;
	if (!nc || !have_key) xocat_helper_errexit("key or cert missing");
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if ((err = getaddrinfo(getenv("XOCAT_BIND"), port, &hints, &ai))) xocat_helper_errexit("bind error");
	for (a = ai; a && nl < 16; a = a->ai_next) {
		int s = socket(a->ai_family, a->ai_socktype, a->ai_protocol);
		if (s < 0) continue;
		setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &one, sizeof one);
		if (a->ai_family == AF_INET6) setsockopt(s, IPPROTO_IPV6, IPV6_V6ONLY, &one, sizeof one);
		if (bind(s, a->ai_addr, a->ai_addrlen) < 0 || listen(s, 16) < 0) { close(s); continue; }
		lfd[nl].fd = s; lfd[nl++].events = POLLIN;
	}
	freeaddrinfo(ai);
	if (!nl) xocat_helper_errexit("cannot listen");
	signal(SIGCHLD, SIG_IGN);
	for (;;) {
		struct sockaddr_storage ss;
		socklen_t sl = sizeof ss;
		char host[NI_MAXHOST] = "?";
		if (poll(lfd, nl, -1) < 0) {
			if (errno == EINTR) continue;
			xocat_helper_errexit("fatal poll error, restart process");
		}
		for (i = 0; i < nl; i++) {
			if (!(lfd[i].revents & POLLIN)) continue;
			sl = sizeof ss;
			if ((sock = accept(lfd[i].fd, (struct sockaddr *)&ss, &sl)) < 0) continue;
			if (fork() != 0) { close(sock); continue; }
			for (n = 0; n < nl; n++) close(lfd[n].fd); // connection handler
			signal(SIGCHLD, SIG_DFL);
			alarm(30); // handshake + hello must arrive in time
			getnameinfo((struct sockaddr *)&ss, sl, host, sizeof host, NULL, 0, NI_NUMERICHOST);
			fprintf(stderr, "xocat: connection from %s\n", host);
			xocat_helper_nonblock(sock);
			br_ssl_server_init_full_ec(&sc, chain, nc, BR_KEYTYPE_EC, br_skey_decoder_get_ec(&skd));
			br_ssl_engine_set_buffer(&sc.eng, iobuf, sizeof iobuf, 1);
			br_ssl_server_reset(&sc);
			err = xocat_pump(&sc.eng, 1);
			if (err > 0) fprintf(stderr, "xocat: %s: TLS error %d\n", host, err);
			if (child > 0) kill(-child, SIGHUP);
			_exit(0);
		}
	}
}

static int xocat_client_main(const char *host, const char *port) {
	static br_ssl_client_context cc;
	static br_x509_minimal_context xc;
	br_x509_trust_anchor *tas = NULL;
	struct addrinfo hints, *ai, *a;
	unsigned char addr[16];
	const char *ca = getenv("XOCAT_CA"), *name = host;
	int nta = 0, i, n, err;
	pem_t *objs = NULL;
	errno = 0;
	if (!port) xocat_helper_errexit("no port given (argument or PORT)");
	if (!ca) xocat_helper_errexit("set XOCAT_CA=file.pem (for testing: demo/cert.pem)");
	n = xocat_certificate(ca, &objs, 0);
	for (i = 0; i < n; i++) {
		br_x509_decoder_context dc;
		br_x509_pkey *pk;
		br_x509_trust_anchor *ta;
		buf_t dn = {0};
		if (!strstr(objs[i].name, "CERTIFICATE")) continue;
		br_x509_decoder_init(&dc, xocat_helper_append2buf, &dn);
		br_x509_decoder_push(&dc, objs[i].der.data, objs[i].der.len);
		if (!(pk = br_x509_decoder_get_pkey(&dc)) || pk->key_type != BR_KEYTYPE_EC) xocat_helper_errexit("XOCAT_CA must contain EC certificates");
		if (!(tas = realloc(tas, (nta + 1) * sizeof *tas))) xocat_helper_errexit("out of memory");
		ta = &tas[nta++];
		ta->dn.data = dn.data;
		ta->dn.len = dn.len;
		ta->flags = br_x509_decoder_isCA(&dc) ? BR_X509_TA_CA : 0;
		ta->pkey = *pk;
		ta->pkey.key.ec.q = xocat_helper_alloc_copy(pk->key.ec.q, pk->key.ec.qlen);
	}
	if (!nta) xocat_helper_errexit("no certificates in XOCAT_CA");
	if (inet_pton(AF_INET, host, addr) == 1 || inet_pton(AF_INET6, host, addr) == 1) xocat_helper_errexit("host name required");
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	if ((err = getaddrinfo(host, port, &hints, &ai))) {
		fprintf(stderr, "xocat: %s\n", gai_strerror(err));
		return 1;
	}
	for (a = ai; a; a = a->ai_next) {
		if ((sock = socket(a->ai_family, a->ai_socktype, a->ai_protocol)) < 0) continue;
		if (connect(sock, a->ai_addr, a->ai_addrlen) == 0) break;
		close(sock);
		sock = -1;
	}
	freeaddrinfo(ai);
	if (sock < 0) xocat_helper_errexit("cannot connect");
	xocat_helper_nonblock(sock);
	br_ssl_client_init_full(&cc, &xc, tas, nta);
	br_ssl_engine_set_buffer(&cc.eng, iobuf, sizeof iobuf, 1);
	br_ssl_client_reset(&cc, name, 0);
	struct termios t; struct sigaction sa;
	if (tcgetattr(0, &saved_tio) < 0) xocat_helper_errexit("stdin is not a terminal");
	t = saved_tio; cfmakeraw(&t);
	if (tcsetattr(0, TCSAFLUSH, &t) < 0) xocat_helper_errexit("cannot set raw mode");
	atexit(xocat_helper_restore_tty);
	memset(&sa, 0, sizeof sa);
	sa.sa_handler = xocat_helper_on_winch;
	sigaction(SIGWINCH, &sa, NULL);
	err = xocat_pump(&cc.eng, 0);
	xocat_helper_restore_tty();
	if (err > 0) {
		fprintf(stderr, "xocat: TLS error %d%s\n", err, err >= 32 && err < 64 ? " (certificate not accepted, see XOCAT_CA)" : "");
		return 1;
	}
	return err < 0 && !sent_hello ? 1 : 0;
}

int main(int argc, char **argv) {
	signal(SIGPIPE, SIG_IGN);
	if (argc >= 3 && !strcmp(argv[1], "server")) return xocat_server_main(argv + 2);
	if (argc >= 3 && !strcmp(argv[1], "client")) return xocat_client_main(argv[2], argc > 3 ? argv[3] : getenv("PORT"));
	fprintf(stderr,
		"usage: PORT=n XOCAT_CERT=cert.pem XOCAT_KEY=key.pem xocat server program [args...]\n"
		"       XOCAT_CA=cert.pem xocat client host [port]\n");
	return 2;
}
