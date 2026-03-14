#define _GNU_SOURCE 

#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../xo.h"
#include <server.h>

#ifdef LIBCURL
#include "net.h"
#endif

#include "json.h"
#include "vault.h"
#include "http.h"
#include "mariadb.h"
#include "pattern.h"

#ifdef FFI
#include "fficonnect.h"
#endif

ctr_object* serverObject;
ctr_object* formatObject;

void ctr_internal_server_init(void) {
	
}

ctr_object* ctr_server_new(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* instance = ctr_internal_create_object(CTR_OBJECT_TYPE_OTEX);
	instance->link = myself;
	return instance;
}

ctr_object* ctr_server_htmlencode_set(ctr_object* myself, ctr_argument* argumentList) {
	char* source = ctr_heap_allocate_cstring(
		ctr_internal_cast2string(argumentList->object)
	);
    size_t len = 0;
	char* p;
    for (p = source; *p; p++) {
        switch (*p) {
            case '&':  len += 5; break;  // &amp;
            case '<':  len += 4; break;  // &lt;
            case '>':  len += 4; break;  // &gt;
            case '"':  len += 6; break;  // &quot;
            case '\'': len += 6; break;  // &#039;
            default:   len += 1; break;
        }
    }
    char* dest = ctr_heap_allocate(len + 1);
	if (!dest) {
		ctr_error("Out of memory while creating html output buffer.", 0);
		ctr_heap_free(source);
		return CtrStdNil;
	}
    char *o = dest;
    for (p = source; *p; p++) {
        switch (*p) {
            case '&':
                memcpy(o, "&amp;", 5);  o += 5;
                break;
            case '<':
                memcpy(o, "&lt;", 4);   o += 4;
                break;
            case '>':
                memcpy(o, "&gt;", 4);   o += 4;
                break;
            case '"':
                memcpy(o, "&quot;", 6); o += 6;
                break;
            case '\'':
                memcpy(o, "&#039;", 6);  o += 6;
                break;
            default:
                *o++ = *p;
        }
    }
    *o = '\0';
    ctr_object* dest_obj = ctr_build_string_from_cstring(dest);
    ctr_heap_free(dest);
    ctr_heap_free(source);
    return dest_obj;
}

/**
 * @def
 * [ Format ] new apply: [ String ]
 *
 * @test536
 */
ctr_object* ctr_format_new(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* instance = ctr_internal_create_object(CTR_OBJECT_TYPE_OTOBJECT);
	instance->link = myself;
	return instance;
}

ctr_object* ctr_format_format_set(ctr_object* myself, ctr_argument* argumentList) {
	ctr_internal_object_property(myself,
		"_format",
		ctr_internal_cast2string(argumentList->object)
	);
	return myself;
}

ctr_object* ctr_format_new_set(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* instance = ctr_format_new(myself, argumentList);
	ctr_format_format_set(instance, argumentList);
	return instance;
}

ctr_object* ctr_format_apply_to_general(ctr_object* myself, ctr_argument* argumentList, int cast) {
	ctr_object* format = ctr_internal_object_property(myself, "_format", NULL);
	if (format == CtrStdNil) return CtrStdNil;
	char* format_str = ctr_heap_allocate_cstring(format);
	ctr_object* value = argumentList->object;
	char* result = "";
	char* s;
	ctr_object* answer;
	if (value->info.type == CTR_OBJECT_TYPE_OTSTRING) {
		s = ctr_heap_allocate_cstring(value);
		asprintf(&result, format_str, s);
		ctr_heap_free(s);
		answer = ctr_build_string_from_cstring(result);
		free(result);
	} else if (value->info.type == CTR_OBJECT_TYPE_OTNUMBER)  {
		if (cast == 1) {
			// cast to int (to print octals or decimals for instance %o/%d etc..)
			asprintf(&result, format_str, (int) value->value.nvalue);
		} else {
			asprintf(&result, format_str, (double) value->value.nvalue);
		}
		answer = ctr_build_string_from_cstring(result);
		free(result);
	} else {
		answer = ctr_build_string_from_cstring(format_str);
	}
	ctr_heap_free(format_str);
	return answer;
}

ctr_object* ctr_format_apply_to(ctr_object* myself, ctr_argument* argumentList) {
	return ctr_format_apply_to_general(myself, argumentList, 0);
}

// because xoscript only works with floats, cast to int and set format cast = 1
// yes, this is not ideal, but in a scripting context it's good enough
ctr_object* ctr_format_apply_int_to(ctr_object* myself, ctr_argument* argumentList) {
	return ctr_format_apply_to_general(myself, argumentList, 1);
}

/**
 * Encodes RFC 3986 or application/form.
 * RFC 3986 encodes space as %20 while form encoding uses +.
 */
static ctr_object* ctr_server_urlformencode(ctr_object* myself, ctr_argument* argumentList, int is_form) {
	char* source = ctr_heap_allocate_cstring(
		ctr_internal_cast2string(argumentList->object)
	);
    size_t len = 0;
	char *p;
    for (p = source; *p; p++) {
        if (*p == ' ' || *p == '-' || *p == '_' || *p == '.' || *p == '~' || isalnum((unsigned char)*p)) { //RFC 3986 unreserved characters
            len += 1;
        } else {
            len += 3; // %HH
        }
    }
	char* dest = ctr_heap_allocate(len + 1);
	if (!dest) {
		ctr_error("Out of memory while creating urlencoded output buffer.", 0);
		ctr_heap_free(source);
		return CtrStdNil;
	}
    char *o = dest;
    for (p = source; *p; p++) {
        if (*p == ' ' && is_form) {
            *o++ = '+';
        } else if (*p == '-' || *p == '_' || *p == '.' || *p == '~' || isalnum((unsigned char)*p)) {
			*o++ = *p;
        } else {
            sprintf(o, "%%%02X", (unsigned char)*p);
            o += 3;
        }
    }
    *o = '\0';
    ctr_object* dest_obj = ctr_build_string_from_cstring(dest);
    ctr_heap_free(dest);
    ctr_heap_free(source);
    return dest_obj;
}

/**
 * @def
 * [ Server ] url-encode: [ String ]
 *
 * @test673
 */
ctr_object* ctr_server_urlencode_set(ctr_object* myself, ctr_argument* argumentList) {
    return ctr_server_urlformencode(myself, argumentList, 0);
}

/**
 * @def
 * [ Server ] form-encode: [ String ]
 *
 * @test673
 */
ctr_object* ctr_server_formencode_set(ctr_object* myself, ctr_argument* argumentList) {
    return ctr_server_urlformencode(myself, argumentList, 1);
}

/**
 * @def
 * [ Server ] base64-encode: [ String ]
 * 
 * @test621
 */
ctr_object* ctr_server_base64encode_set(ctr_object* myself, ctr_argument* argumentList) {
	char* in;
	char* out;
	int outlen;
	int inlen;
	ctr_object* str;
	ctr_object* answer;
	str = ctr_internal_cast2string(argumentList->object);
	inlen = str->value.svalue->vlen;
	if (inlen==0) return ctr_build_empty_string();
	in = ctr_heap_allocate_cstring(str);
	outlen = BASE64_ENCODE_OUT_SIZE(inlen);
	out = ctr_heap_allocate(outlen);
	outlen = base64_encode((unsigned char*)in, inlen, out);
	answer = ctr_build_string_from_cstring(out);
	ctr_heap_free(in);
	ctr_heap_free(out);
	return answer;
}

/**
 * @def
 * [ Server ] base64-decode: [ String ]
 * 
 * @test621
 */
ctr_object* ctr_server_base64decode_set(ctr_object* myself, ctr_argument* argumentList) {
	char* in;
	char* out;
	int outlen;
	int inlen;
	ctr_object* str;
	ctr_object* answer;
	str = ctr_internal_cast2string(argumentList->object);
	inlen = str->value.svalue->vlen;
	if (inlen==0) return ctr_build_empty_string();
	in = ctr_heap_allocate_cstring(str);
	outlen = BASE64_DECODE_OUT_SIZE(inlen);
	out = ctr_heap_allocate(outlen);
	outlen = base64_decode(in, inlen, (unsigned char*) out);
	answer = ctr_build_string(out, outlen);
	ctr_heap_free(in);
	ctr_heap_free(out);
	return answer;
}

/**
 * @def
 * [ Server ] link: [ List ]
 * 
 * @test130
 */
ctr_object* ctr_server_link_set(ctr_object* myself, ctr_argument* argumentList) {
	if (argumentList->object->link == CtrStdArray) {
		#ifdef FFI
		ctr_internal_gui_ffi(argumentList->object);
		#else
		ctr_error("FFI not available.", 0);
		#endif
	}
	return myself;
}

#define CTR_SERVER_MIMETYPE_UNKNOWN 0
#define CTR_SERVER_MIMETYPE_JPEG    1
#define CTR_SERVER_MIMETYPE_GIF     2
#define CTR_SERVER_MIMETYPE_PNG     3
#define CTR_SERVER_MIMETYPE_PDF     4
#define CTR_SERVER_MIMETYPE_ZIP     5
#define CTR_SERVER_MIMETYPE_GZIP    6
#define CTR_SERVER_MIMETYPE_MP3     7
#define CTR_SERVER_MIMETYPE_MP4     8
#define CTR_SERVER_MIMETYPE_WEBP    9
#define CTR_SERVER_MIMETYPE_WEBM    10
#define CTR_SERVER_MIMETYPE_SVG     11

int ctr_internal_server_detect_mimetype(unsigned char *buf, size_t len) {
    if (len < 4) return CTR_SERVER_MIMETYPE_UNKNOWN;
    if (len >= 3 &&
        buf[0] == 0xFF &&
        buf[1] == 0xD8 &&
        buf[2] == 0xFF) {
        return CTR_SERVER_MIMETYPE_JPEG;
    }
    if (len >= 5 && memcmp(buf, "<svg ", 5)==0) {
        return CTR_SERVER_MIMETYPE_SVG;
    }
    if (len >= 6 &&
        (!memcmp(buf, "GIF87a", 6) ||
         !memcmp(buf, "GIF89a", 6))) {
        return CTR_SERVER_MIMETYPE_GIF;
    }
    if (len >= 8 &&
        !memcmp(buf, "\x89PNG\r\n\x1A\n", 8)) {
        return CTR_SERVER_MIMETYPE_PNG;
    }
    if (len >= 5 &&
        !memcmp(buf, "%PDF-", 5)) {
        return CTR_SERVER_MIMETYPE_PDF;
    }
    if (len >= 4 &&
        !memcmp(buf, "PK\x03\x04", 4)) {
        return CTR_SERVER_MIMETYPE_ZIP;
    }
    if (len >= 2 &&
        buf[0] == 0x1F &&
        buf[1] == 0x8B) {
        return CTR_SERVER_MIMETYPE_GZIP;
    }
    /* MP3 (ID3 tag or MPEG frame) */
    if ((len >= 3 && !memcmp(buf, "ID3", 3)) ||
        (len >= 2 && buf[0] == 0xFF && (buf[1] & 0xE0) == 0xE0)) {
        return CTR_SERVER_MIMETYPE_MP3;
    }
    /* MP4 (ftyp box at offset 4) */
    if (len >= 12 &&
        !memcmp(buf + 4, "ftyp", 4)) {
        return CTR_SERVER_MIMETYPE_MP4;
    }
    /* WEBP (RIFF + WEBP) */
    if (len >= 12 &&
        !memcmp(buf, "RIFF", 4) &&
        !memcmp(buf + 8, "WEBP", 4)) {
        return CTR_SERVER_MIMETYPE_WEBP;
    }
    /* WEBM (Matroska) */
    if (len >= 4 &&
        buf[0] == 0x1A &&
        buf[1] == 0x45 &&
        buf[2] == 0xDF &&
        buf[3] == 0xA3) {
        return CTR_SERVER_MIMETYPE_WEBM;
    }
    return CTR_SERVER_MIMETYPE_UNKNOWN;
}

/**
 * @def
 * [ Server ] passthru: [ String ] prefix: [ String ]
 *
 * @test497
 */
#define MAX_ASSET_SIZE (50 * 1024 * 1024)
ctr_object* ctr_server_passthru_set(ctr_object* myself, ctr_argument* argumentList) {
	char* pathstr;
	char* prefixstr;
	char peekbuf[12];
	prefixstr = ctr_heap_allocate_cstring(
		ctr_internal_cast2string(argumentList->next->object)
	);
	pathstr = ctr_heap_allocate_cstring(
		ctr_internal_cast2string(argumentList->object)
	);
	if (strchr(pathstr, '/')!=NULL || strstr(pathstr,"..")!=NULL) {
		ctr_heap_free(pathstr);
		ctr_heap_free(prefixstr);
		ctr_error("Illegal path", 0);
		return CtrStdNil;
	}
	int dirfd = open(prefixstr, O_RDONLY | O_DIRECTORY);
	ctr_heap_free(prefixstr);
	if (dirfd < 0) {
		ctr_heap_free(pathstr);
		ctr_error("Unable to open prefix", 0);
		return CtrStdNil;
	}
	int fd = openat(dirfd, pathstr, O_RDONLY | O_NOFOLLOW);
	close(dirfd);
	ctr_heap_free(pathstr);
	if (fd < 0) {
		ctr_error("Unable to open path", 0);
		return CtrStdNil;
	}
	struct stat st;
	if (fstat(fd, &st) < 0  || !S_ISREG(st.st_mode) || st.st_size > MAX_ASSET_SIZE) {
		close(fd);
		ctr_error("Unable to get filesize or too big", 0);
		return CtrStdNil;
	}
	size_t r = pread(fd, peekbuf, 12, 0);
	if (r < 12) {
		close(fd);
		ctr_error("Unable to scan mimetype", 0);
		return CtrStdNil;
	}
	int mimetype = ctr_internal_server_detect_mimetype((unsigned char*)peekbuf, r);
	if (mimetype == CTR_SERVER_MIMETYPE_UNKNOWN) {
		// mimetype must be in whitelist
		close(fd);
		ctr_error("Unable to scan mimetype", 0);
		return CtrStdNil;
	}
	switch(mimetype) {
		case CTR_SERVER_MIMETYPE_JPEG:
			printf("Content-Type: image/jpeg\r\n");
			break;
		case CTR_SERVER_MIMETYPE_PNG:
			printf("Content-Type: image/png\r\n");
			break;
		case CTR_SERVER_MIMETYPE_GIF:
			printf("Content-Type: image/gif\r\n");
			break;
		case CTR_SERVER_MIMETYPE_WEBP:
			printf("Content-Type: image/webp\r\n");
			break;
		case CTR_SERVER_MIMETYPE_MP3:
			printf("Content-Type: audio/mpeg\r\n");
			break;
		case CTR_SERVER_MIMETYPE_MP4:
			printf("Content-Type: video/mp4\r\n");
			break;
		case CTR_SERVER_MIMETYPE_WEBM:
			printf("Content-Type: video/webm\r\n");
			break;
		case CTR_SERVER_MIMETYPE_ZIP:
			printf("Content-Type: application/zip\r\n");
			printf("Content-Disposition: attachment\r\n");
			break;
		case CTR_SERVER_MIMETYPE_GZIP:
			printf("Content-Type: application/gzip\r\n");
			printf("Content-Disposition: attachment\r\n");
			break;
		case CTR_SERVER_MIMETYPE_PDF:
			printf("Content-Type: application/pdf\r\n");
			break;
		case CTR_SERVER_MIMETYPE_SVG:
			printf("Content-Type: image/svg+xml\r\n");
			break;
	}
	printf("Content-Length: %lld\r\n", (long long)st.st_size);
	printf("X-Content-Type-Options: nosniff\r\n\r\n");
	fflush(stdout);
	char buf[4096];
	ssize_t n;
	while ((n = read(fd, buf, sizeof buf)) > 0) {
		ssize_t off = 0;
		while (off < n) {
			ssize_t w = write(STDOUT_FILENO, buf + off, n - off);
			if (w < 0) {
				ctr_error("Write error", 0);
				goto out;
			}
			off += w;
		}
	}
	if (n < 0) {
		ctr_error("Read error", 0);
		goto out;
	}
	out:
	close(fd);
	return myself;
}

/**
 * @def
 * [ Server ] mimetype: [ String ]
 *
 * @test657
 */
ctr_object* ctr_server_mimetype(ctr_object* myself, ctr_argument* argumentList) {
	char* pathstr;
	char peekbuf[12];
	ctr_object* mimetype = CtrStdNil;
	pathstr = ctr_heap_allocate_cstring(
		ctr_internal_cast2string(argumentList->object)
	);
	FILE* f = fopen(pathstr,"rb");
	ctr_heap_free(pathstr);
	if (f == NULL) {
		ctr_error("Unable to open file", 0);
		return CtrStdNil;
	}
	int bytes_read = fread(peekbuf, 1, 12, f);
	fclose(f);
	int m = ctr_internal_server_detect_mimetype((unsigned char*)peekbuf, bytes_read);
	switch(m) {
		case CTR_SERVER_MIMETYPE_UNKNOWN:
			mimetype = ctr_build_string_from_cstring("unknown");
			break;
		case CTR_SERVER_MIMETYPE_JPEG:
			mimetype = ctr_build_string_from_cstring("jpg");
			break;
		case CTR_SERVER_MIMETYPE_PNG:
			mimetype = ctr_build_string_from_cstring("png");
			break;
		case CTR_SERVER_MIMETYPE_GIF:
			mimetype = ctr_build_string_from_cstring("gif");
			break;
		case CTR_SERVER_MIMETYPE_WEBP:
			mimetype = ctr_build_string_from_cstring("webp");
			break;
		case CTR_SERVER_MIMETYPE_MP3:
			mimetype = ctr_build_string_from_cstring("mp3");
			break;
		case CTR_SERVER_MIMETYPE_MP4:
			mimetype = ctr_build_string_from_cstring("mp4");
			break;
		case CTR_SERVER_MIMETYPE_WEBM:
			mimetype = ctr_build_string_from_cstring("webm");
			break;
		case CTR_SERVER_MIMETYPE_ZIP:
			mimetype = ctr_build_string_from_cstring("zip");
			break;
		case CTR_SERVER_MIMETYPE_GZIP:
			mimetype = ctr_build_string_from_cstring("gzip");
			break;
		case CTR_SERVER_MIMETYPE_PDF:
			mimetype = ctr_build_string_from_cstring("pdf");
			break;
		case CTR_SERVER_MIMETYPE_SVG:
			mimetype = ctr_build_string_from_cstring("svg");
			break;
	}
	return mimetype;
}

static int is_valid_ipv4(const char *ip) {
    if (ip == NULL) return 0;
    int num, dots = 0;
    const char *ptr = ip;
    while (*ptr) {
        if (!isdigit(*ptr)) return 0;
		num = 0;
        int digits = 0;
        while (*ptr && isdigit(*ptr)) {
            num = num * 10 + (*ptr - '0');
            digits++;
			if (digits > 3) return 0;
            if (num > 255) return 0;
            ptr++;
        }
        if (digits > 1 && *(ptr - digits) == '0') return 0;
        if (*ptr == '.') {
            dots++;
            if (dots > 3) return 0;
            ptr++;
            if (*ptr == '\0') return 0;
        } else if (*ptr != '\0') {
            return 0;
        }
    }
    return dots == 3;
}

static int is_valid_ipv6(const char *ip) {
	if (!ip || *ip == '\0') return 0;
	int blocks = 0;
	int digits = 0;
	int double_colon_seen = 0;
	while (*ip) {
		if (isxdigit((unsigned char)*ip)) {
		digits++;
		if (digits > 4) return 0;
		} else if (*ip == ':') {
			if (*(ip + 1) == ':' && !double_colon_seen) {
				double_colon_seen = 1;
				ip++;
			} else if (digits == 0) {
				return 0;
			}
			blocks++;
			digits = 0;
			} else {
			return 0;
		}
		ip++;
	}
	if (digits > 0) blocks++;
	if (double_colon_seen) return blocks <= 8;
	return blocks == 8;
}

static int is_valid_mac(const char* mac) {
    int i;
    if (!mac) return 0;
    for (i = 0; i < 17; i++) {
        if ((i + 1) % 3 == 0) {
            if (mac[i] != ':') return 0;
        } else {
            if (!isxdigit(mac[i])) return 0;
        }
    }
    return mac[17] == '\0';
}

/**
 * @def
 * [ String ] ipv4?
 *
 * @test684
 */
ctr_object* ctr_string_ipv4(ctr_object* myself, ctr_argument* argumentList) {
	char* str = ctr_heap_allocate_cstring(myself);
	ctr_object* bool = ctr_build_bool(is_valid_ipv4(str));
	ctr_heap_free(str);
	return bool;
}

/**
 * @def
 * [ String ] ipv6?
 *
 * @test685
 */
ctr_object* ctr_string_ipv6(ctr_object* myself, ctr_argument* argumentList) {
	char* str = ctr_heap_allocate_cstring(myself);
	ctr_object* bool = ctr_build_bool(is_valid_ipv6(str));
	ctr_heap_free(str);
	return bool;
}

/**
 * @def
 * [ String ] mac?
 *
 * @test686
 */
ctr_object* ctr_string_mac(ctr_object* myself, ctr_argument* argumentList) {
	char* str = ctr_heap_allocate_cstring(myself);
	ctr_object* bool = ctr_build_bool(is_valid_mac(str));
	ctr_heap_free(str);
	return bool;
}

/**
 * @def
 * [ String ] html
 *
 * @test687
 */
ctr_object* ctr_string_tohtml(ctr_object* myself, ctr_argument* argumentList ) {
	size_t len = 0;
	char* html; char* dst;
	int r,b,it,i;
	r = 0; i = 0; b = 0; it = 0;
	size_t vlen;
	vlen = myself->value.svalue->vlen;
	char* value;
	value = myself->value.svalue->value;
	for(i=0; i<vlen; i++) {
		char c = value[i];
		if (c == '*' && !b)  { len += 3; b=1;  continue; }
		if (c == '*' &&  b)  { len += 4; b=0;  continue; }
		if (c == '_' && !it) { len += 3; it=1; continue; }
		if (c == '_' && it)  { len += 4; it=0; continue; }
		if (c == '\r')       { len += 5; r=1;  continue; } 
		if (!r && c == '\n') { len += 5;       continue; }
		if (r && c == '\n')  { r = 0; }
		len += 1;
	}
	html = ctr_heap_allocate(len + 1);
	dst = html;
	r = 0; i = 0; b = 0; it = 0;
	for(i=0; i<vlen; i++) {
		char c = value[i];
		if (c == '*' && !b)  { memcpy(dst,"<b>",3);    dst += 3; b=1;  continue; }
		if (c == '*' &&  b)  { memcpy(dst,"</b>",4);   dst += 4; b=0;  continue; }
		if (c == '_' && !it) { memcpy(dst,"<i>",3);    dst += 3; it=1; continue; }
		if (c == '_' && it)  { memcpy(dst,"</i>",4);   dst += 4; it=0; continue; }
		if (c == '\r')       { memcpy(dst,"<br>\r",5); dst += 5; r=1;  continue; } 
		if (!r && c == '\n') { memcpy(dst,"<br>\n",5); dst += 5;       continue; }
		if (r && c == '\n')  { r = 0; }
		*dst++ = c;
	}
	ctr_object* result = ctr_build_string_from_cstring(html);
	ctr_heap_free(html);
	return result;
}

void begin() {
	ctr_internal_server_init();
	serverObject = NULL;
	serverObject = ctr_server_new(CtrStdObject, NULL);
	serverObject->link = CtrStdObject;
	ctr_internal_create_func(serverObject, ctr_build_string_from_cstring( CTR_DICT_NEW ), &ctr_server_new );
	ctr_internal_create_func(serverObject, ctr_build_string_from_cstring( "html-encode:" ), &ctr_server_htmlencode_set );
	ctr_internal_create_func(serverObject, ctr_build_string_from_cstring( "url-encode:" ), &ctr_server_urlencode_set );
	ctr_internal_create_func(serverObject, ctr_build_string_from_cstring( "form-encode:" ), &ctr_server_formencode_set );
	ctr_internal_create_func(serverObject, ctr_build_string_from_cstring( "base64-encode:" ), &ctr_server_base64encode_set );
	ctr_internal_create_func(serverObject, ctr_build_string_from_cstring( "base64-decode:" ), &ctr_server_base64decode_set );
	ctr_internal_create_func(serverObject, ctr_build_string_from_cstring( "link:" ), &ctr_server_link_set );
	ctr_internal_create_func(serverObject, ctr_build_string_from_cstring( "passthru:prefix:" ), &ctr_server_passthru_set );
	ctr_internal_create_func(serverObject, ctr_build_string_from_cstring( "mimetype:" ), &ctr_server_mimetype );
	ctr_internal_object_add_property(CtrStdWorld, ctr_build_string_from_cstring( "Server" ), serverObject, CTR_CATEGORY_PUBLIC_PROPERTY);
	//@todo move to core
	formatObject = NULL;
	formatObject = ctr_format_new(CtrStdObject, NULL);
	formatObject->link = CtrStdObject;
	ctr_internal_create_func(formatObject, ctr_build_string_from_cstring( CTR_DICT_NEW ), &ctr_format_new );
	ctr_internal_create_func(formatObject, ctr_build_string_from_cstring( CTR_DICT_NEW_SET ), &ctr_format_new_set );
	ctr_internal_create_func(formatObject, ctr_build_string_from_cstring( "format:" ), &ctr_format_format_set );
	ctr_internal_create_func(formatObject, ctr_build_string_from_cstring( "apply:" ), &ctr_format_apply_to );
	ctr_internal_create_func(formatObject, ctr_build_string_from_cstring( "apply-int:" ), &ctr_format_apply_int_to );
	ctr_internal_object_add_property(CtrStdWorld, ctr_build_string_from_cstring( "Format" ), formatObject, CTR_CATEGORY_PUBLIC_PROPERTY);
	ctr_internal_create_func(CtrStdString, ctr_build_string_from_cstring( "ipv4?" ), &ctr_string_ipv4 );
	ctr_internal_create_func(CtrStdString, ctr_build_string_from_cstring( "ipv6?" ), &ctr_string_ipv6 );
	ctr_internal_create_func(CtrStdString, ctr_build_string_from_cstring( "mac?" ), &ctr_string_mac );
	ctr_internal_create_func(CtrStdString, ctr_build_string_from_cstring( "html" ), &ctr_string_tohtml );
	
	#ifdef LIBCURL
	begin_net();
	#endif
	begin_http();
	begin_json();
	begin_vault();
	begin_mariadb();
	#ifdef FFI
	begin_ffi();
	#endif
	#ifdef PCRE2
	begin_pcre2();
	#endif
}
