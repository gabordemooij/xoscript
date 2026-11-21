xocat

a tiny socat-like tool to run CLI programs (like xoscript files)
over TLS, for humans and agents.

Server:  PORT=4433 XOCAT_CERT=cert.pem XOCAT_KEY=key.pem xocat server ./xo myapp.xo 2>/var/log/err.txt
Client:  XOCAT_CA=cert.pem xocat client example.com 4433

PORT=4433 XOCAT_CERT=demo/cert.pem XOCAT_KEY=demo/key.pem ./xocat server ./xo hello.xo
XOCAT_CA=demo/cert.pem ./xocat client localhost 4433

Environment (server):
  PORT        port to listen on (IPv4 and IPv6)
  XOCAT_BIND  optional address to bind to (default: all)
  XOCAT_CERT  PEM certificate chain (EC)
  XOCAT_KEY   PEM EC private key (default: same file as XOCAT_CERT)
Environment (client):
  PORT        port, if not given on the command line
  XOCAT_CA    PEM file with trusted certificates (a self-signed server
              certificate itself works); hostname is checked.

Every connection forks the target program with a pty as stdin/stdout
(echo, line editing, password input, Ctrl-C, window size, line buffered
 output). Client stdin must be a terminal. AI Agents can emulate this.
 
Protocol (inside TLS): client to server is framed as
[type][len hi][len lo][payload]: 'H' hello (rows, cols),
'D' data, 'W' window size (rows, cols), 'E' end of input.
Server to client is the raw output of the program.
