/*
 * C CGI Library version 1.2
 *
 * Copyright 2015 Stephen C. Losen.  Distributed under the terms
 * of the GNU Lesser General Public License (LGPL 2.1)
 */

#ifndef _CCGI_H
#define _CCGI_H

void CGI_set_max_postfields(size_t n);
void CGI_set_max_contentlength(size_t n);

typedef struct CGI_varlist CGI_varlist;

typedef const char * const CGI_value;
char *CGI_decode_url(const char *p);
char *CGI_encode_url(const char *p, const char *keep);
char *CGI_encode_hex(const void *p, int len);
void *CGI_decode_hex(const char *p, int *len);
char *CGI_encode_query(const char *keep, ...);
char *CGI_encode_varlist(CGI_varlist *v, const char *keep);
CGI_varlist *CGI_decode_query(CGI_varlist *v, const char *query, int ispost);
CGI_varlist *CGI_get_cookie(CGI_varlist *v);
CGI_varlist *CGI_get_query(CGI_varlist *v);
CGI_varlist *CGI_get_post(CGI_varlist *v, const char *template);
CGI_varlist *CGI_get_all(const char *template);
CGI_varlist *CGI_add_var(CGI_varlist *v, const char *varname,
    const char *value);

void CGI_free_varlist(CGI_varlist *v);
CGI_value *CGI_lookup_all(CGI_varlist *v, const char *varname);
const char *CGI_lookup(CGI_varlist *v, const char *varname);
const char *CGI_first_name(CGI_varlist *v);
const char *CGI_next_name(CGI_varlist *v);
int CGI_parse_url(char* url, char* scheme, char* host, char* port, char* path, char* query, char* fragment);

#endif
