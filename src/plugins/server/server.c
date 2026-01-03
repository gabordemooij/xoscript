#define _GNU_SOURCE 

#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../citrine.h"
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

/**
 * Use this error handler if init or critical operation fails.
 */
void ctr_internal_gui_fatalerror(char* msg, const char* info)	{
	fprintf(stderr,"GUI FATAL ERROR: %s (%s) \n", msg, info);
	exit(1);
}

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

ctr_object* ctr_format_apply_to(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* format = ctr_internal_object_property(myself, "_format", NULL);
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
		asprintf(&result, format_str, (double) value->value.nvalue);
		answer = ctr_build_string_from_cstring(result);
		free(result);
	} else {
		answer = ctr_build_string_from_cstring(format_str);
	}
	ctr_heap_free(format_str);
	return answer;
}


ctr_object* ctr_server_urlencode_set(ctr_object* myself, ctr_argument* argumentList) {
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
        if (*p == ' ') {
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
 * @def [ Server ] base64-encode: [ String ]
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
	outlen = base64_encode(in, inlen, out);
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
	outlen = base64_decode(in, inlen, out);
	answer = ctr_build_string(out, outlen);
	ctr_heap_free(in);
	ctr_heap_free(out);
	return answer;
}

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

void begin() {
	ctr_internal_server_init();
	serverObject = NULL;
	serverObject = ctr_server_new(CtrStdObject, NULL);
	serverObject->link = CtrStdObject;
	ctr_internal_create_func(serverObject, ctr_build_string_from_cstring( CTR_DICT_NEW ), &ctr_server_new );
	ctr_internal_create_func(serverObject, ctr_build_string_from_cstring( "html-encode:" ), &ctr_server_htmlencode_set );
	ctr_internal_create_func(serverObject, ctr_build_string_from_cstring( "url-encode:" ), &ctr_server_urlencode_set );
	ctr_internal_create_func(serverObject, ctr_build_string_from_cstring( "base64-encode:" ), &ctr_server_base64encode_set );
	ctr_internal_create_func(serverObject, ctr_build_string_from_cstring( "base64-decode:" ), &ctr_server_base64decode_set );
	ctr_internal_create_func(serverObject, ctr_build_string_from_cstring( "link:" ), &ctr_server_link_set );
	ctr_internal_object_add_property(CtrStdWorld, ctr_build_string_from_cstring( "Server" ), serverObject, CTR_CATEGORY_PUBLIC_PROPERTY);
	//@todo move to core
	formatObject = NULL;
	formatObject = ctr_format_new(CtrStdObject, NULL);
	formatObject->link = CtrStdObject;
	ctr_internal_create_func(formatObject, ctr_build_string_from_cstring( CTR_DICT_NEW ), &ctr_format_new );
	ctr_internal_create_func(formatObject, ctr_build_string_from_cstring( CTR_DICT_NEW_SET ), &ctr_format_new_set );
	ctr_internal_create_func(formatObject, ctr_build_string_from_cstring( "format:" ), &ctr_format_format_set );
	ctr_internal_create_func(formatObject, ctr_build_string_from_cstring( "apply:" ), &ctr_format_apply_to );
	ctr_internal_object_add_property(CtrStdWorld, ctr_build_string_from_cstring( "Format" ), formatObject, CTR_CATEGORY_PUBLIC_PROPERTY);
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

void init_embedded_gui_plugin() {
	begin();
}
