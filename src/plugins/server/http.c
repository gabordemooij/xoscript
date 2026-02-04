#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>
#include <stdint.h>
#include <unistd.h>
#include <syslog.h>
#include "../../xo.h"

#include "i18n/en/server.h"

#include "ccgi/ccgi.h"

CGI_varlist *varlistGet;
CGI_varlist *varlistPost;
CGI_varlist *varlistCookie;
ctr_object* CtrStdSCGICB;
ctr_object* requestObject;
ctr_object* urlObject;

/**
 * @internal
 * 
 * Returns a string from the request, either for GET, POST or COOKIE.
 */
ctr_object* ctr_request_string(ctr_object* myself, ctr_argument* argumentList, CGI_varlist* varlist) {
	ctr_object* cgiVarObject;
	char* cgiVar;
	char* value;
	cgiVarObject = ctr_internal_cast2string(argumentList->object);
	cgiVar = ctr_heap_allocate_cstring( cgiVarObject );
	value = (char*) CGI_lookup(varlist, (const char*)cgiVar);
	ctr_heap_free( cgiVar );
	if (value == NULL) return CtrStdNil;
	return ctr_build_string_from_cstring(value);
}

/**
 * @internal
 * 
 * Returns an array from the request, either for GET, POST or COOKIE.
 */
ctr_object* ctr_request_array(ctr_object* myself, ctr_argument* argumentList, CGI_varlist* varlist) {
	ctr_object* cgiVarObject;
	ctr_object* list;
	char* cgiVar;
	const CGI_value* value;
	char* val;
	ctr_argument* arg;
	int i = 0;
	list = ctr_array_new(CtrStdArray, NULL);	
	cgiVarObject = ctr_internal_cast2string(argumentList->object);
	cgiVar = ctr_heap_allocate_cstring( cgiVarObject );
	value = CGI_lookup_all(varlist, (const char*)cgiVar);
	ctr_heap_free( cgiVar );
	if (value == NULL) {
		return list;
	}
	for (i = 0; value[i] != 0; i++) {
		arg = (ctr_argument*) ctr_heap_allocate( sizeof( ctr_argument ) );
		val = (char*) value[i];
		arg->object = ctr_build_string_from_cstring(val);
		ctr_array_push(list, arg);
		ctr_heap_free( arg );
	}
	return list;
}

/**
 * @def
 * [ Request ] get: [ String ]
 */
ctr_object* ctr_request_get_string(ctr_object* myself, ctr_argument* argumentList) {
	return ctr_request_string(myself, argumentList, varlistGet);
}

/**
 * @def
 * [ Request ] get-list: [ String ]
 */
ctr_object* ctr_request_get_array(ctr_object* myself, ctr_argument* argumentList) {
	return ctr_request_array(myself, argumentList, varlistGet);
}

/**
 * @def
 * [ Request ] post: [ String ]
 */
ctr_object* ctr_request_post_string(ctr_object* myself, ctr_argument* argumentList) {
	return ctr_request_string(myself, argumentList, varlistPost);
}

/**
 * @def
 * [ Request ] post-list: [ String ]
 */
ctr_object* ctr_request_post_array(ctr_object* myself, ctr_argument* argumentList) {
	return ctr_request_array(myself, argumentList, varlistPost);
}

/**
 * @def
 * [ Request ] cookie: [ String ]
 */
ctr_object* ctr_request_cookie_string(ctr_object* myself, ctr_argument* argumentList) {
	return ctr_request_string(myself, argumentList, varlistCookie);
}

/**
 * @def
 * [ Request ] cookie-list: [ String ]
 */
ctr_object* ctr_request_cookie_array(ctr_object* myself, ctr_argument* argumentList) {
	return ctr_request_array(myself, argumentList, varlistCookie);
}

/**
 * @def
 * [ Request ] upload: [ String ]
 */
ctr_object* ctr_request_file(ctr_object* myself, ctr_argument* argumentList) {
	CGI_value* value;
	ctr_object* list;
	ctr_object* cgiVarObject;
	char* cgiVar;
	char* val;
	ctr_argument* arg;
	int i = 0;
	cgiVarObject = ctr_internal_cast2string(argumentList->object);
	cgiVar = ctr_heap_allocate_cstring( cgiVarObject );
	value = CGI_lookup_all(varlistPost, (const char*)cgiVar);
	ctr_heap_free( cgiVar );
    list = ctr_array_new(CtrStdArray, NULL);
	if (value == 0 || value[1] == 0) return list;
    for (i = 0; value[i] != 0; i++) {
		arg = (ctr_argument*) ctr_heap_allocate( sizeof( ctr_argument ) );
		val = (char*) value[i];
		arg->object = ctr_build_string_from_cstring(val);
		ctr_array_push(list, arg);
		ctr_heap_free( arg );
	}
	return list;
}


/**
 * @def
 * [ URL ] from: [ String ]
 *
 * @test636
 */
CTR_DEFINE_CLASS_OTOBJECT(ctr_url_new);
CTR_DEFINE_GETTER(ctr_url_scheme,   "scheme");
CTR_DEFINE_GETTER(ctr_url_host,     "host");
CTR_DEFINE_GETTER(ctr_url_port,     "port");
CTR_DEFINE_GETTER(ctr_url_path,     "path");
CTR_DEFINE_GETTER(ctr_url_query,    "query");
CTR_DEFINE_GETTER(ctr_url_fragment, "fragment");

ctr_object* ctr_url_from_set(ctr_object* myself, ctr_argument* argumentList) {
	char* urlstr = ctr_heap_allocate_cstring(
		ctr_internal_copy2string(
			argumentList->object
		)
	);
	char scheme[32 + 1];
	char host[512 + 1];
	char port[64 + 1];
	char path[1024 + 1];
	char query[1024 + 1];
	char fragment[256 + 1];
	memset(scheme,   0, 32 + 1);
	memset(host,     0, 512 + 1);
	memset(port,     0, 64 + 1);
	memset(path,     0, 1024 + 1);
	memset(query,    0, 1024 + 1);
	memset(fragment, 0, 256 + 1);
	int err = CGI_parse_url(urlstr, scheme, host, port, path, query, fragment);
	ctr_heap_free(urlstr);
	if (err) {
		ctr_error("Unable to parse url", 0);
		return CtrStdNil;
	}
	ctr_object* url = ctr_url_new(urlObject, argumentList);
	ctr_internal_object_property(url, "scheme", ctr_build_string_from_cstring(scheme));
	ctr_internal_object_property(url, "host", ctr_build_string_from_cstring(host));
	ctr_internal_object_property(url, "port", ctr_build_number(port));
	ctr_internal_object_property(url, "path", ctr_build_string_from_cstring(path));
	ctr_internal_object_property(url, "query", ctr_build_string_from_cstring(query));
	ctr_internal_object_property(url, "fragment", ctr_build_string_from_cstring(fragment));
	return url;
}


/**
 * @internal
 *
 * Adds the Request object to the World.
 */
void begin_http(){
	char* maxpostfields_str = getenv("max-postfields");
	size_t maxpostfields = 0;
	if (maxpostfields_str == NULL) {
		maxpostfields_str = "40";
	}
	maxpostfields = (size_t) atoi(maxpostfields_str);
	CGI_set_max_postfields(maxpostfields);
	char* maxcontentlength_str = getenv("max-contentlength");
	size_t maxcontentlength = 0;
	if (maxcontentlength_str == NULL) {
		maxcontentlength_str = "2000000"; //2 MB
	}
	maxcontentlength = (size_t) atoi(maxcontentlength_str);
	CGI_set_max_contentlength(maxcontentlength);
	requestObject = ctr_internal_create_object(CTR_OBJECT_TYPE_OTOBJECT);
	requestObject->link = CtrStdObject;
	ctr_internal_create_func(requestObject, ctr_build_string_from_cstring( CTR_DICT_HTTP_REQUEST_GET_SET ), &ctr_request_get_string );
	ctr_internal_create_func(requestObject, ctr_build_string_from_cstring( CTR_DICT_HTTP_REQUEST_GET_LIST_SET ), &ctr_request_get_array );
	ctr_internal_create_func(requestObject, ctr_build_string_from_cstring( CTR_DICT_HTTP_REQUEST_COOKIE_SET ), &ctr_request_cookie_string );
	ctr_internal_create_func(requestObject, ctr_build_string_from_cstring( CTR_DICT_HTTP_REQUEST_COOKIE_LIST_SET ), &ctr_request_cookie_array );
	ctr_internal_create_func(requestObject, ctr_build_string_from_cstring( CTR_DICT_HTTP_REQUEST_POST_SET ), &ctr_request_post_string );
	ctr_internal_create_func(requestObject, ctr_build_string_from_cstring( CTR_DICT_HTTP_REQUEST_UPLOAD_SET ), &ctr_request_file );
	ctr_internal_create_func(requestObject, ctr_build_string_from_cstring( CTR_DICT_HTTP_REQUEST_POST_LIST_SET ), &ctr_request_post_array );
	ctr_internal_object_add_property(CtrStdWorld, ctr_build_string_from_cstring( CTR_DICT_PLUGIN_REQUEST ), requestObject, 0);
	varlistGet = CGI_get_query(NULL);
	varlistPost = CGI_get_post(NULL,"/tmp/_upXXXXXX");
	varlistCookie = CGI_get_cookie(NULL);
	urlObject = ctr_url_new(CtrStdObject, NULL);
	urlObject->link = CtrStdObject;
	ctr_internal_create_func(urlObject, ctr_build_string_from_cstring( CTR_DICT_NEW ), &ctr_url_new );
	ctr_internal_create_func(urlObject, ctr_build_string_from_cstring( "from:" ), &ctr_url_from_set );
	ctr_internal_create_func(urlObject, ctr_build_string_from_cstring( "scheme" ), &ctr_url_scheme );
	ctr_internal_create_func(urlObject, ctr_build_string_from_cstring( "host" ), &ctr_url_host );
	ctr_internal_create_func(urlObject, ctr_build_string_from_cstring( "port" ), &ctr_url_port );
	ctr_internal_create_func(urlObject, ctr_build_string_from_cstring( "path" ), &ctr_url_path );
	ctr_internal_create_func(urlObject, ctr_build_string_from_cstring( "query" ), &ctr_url_query );
	ctr_internal_create_func(urlObject, ctr_build_string_from_cstring( "fragment" ), &ctr_url_fragment );
	ctr_internal_object_add_property(CtrStdWorld, ctr_build_string_from_cstring( "URL" ), urlObject, 0);
}
