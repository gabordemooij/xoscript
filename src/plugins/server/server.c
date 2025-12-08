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


void begin() {
	ctr_internal_server_init();
	serverObject = NULL;
	serverObject = ctr_server_new(CtrStdObject, NULL);
	serverObject->link = CtrStdObject;
	ctr_internal_create_func(serverObject, ctr_build_string_from_cstring( CTR_DICT_NEW ), &ctr_server_new );
	ctr_internal_create_func(serverObject, ctr_build_string_from_cstring( "html-encode:" ), &ctr_server_htmlencode_set );
	ctr_internal_object_add_property(CtrStdWorld, ctr_build_string_from_cstring( "Server" ), serverObject, CTR_CATEGORY_PUBLIC_PROPERTY);
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
