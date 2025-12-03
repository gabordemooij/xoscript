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

void begin() {
	ctr_internal_server_init();
	serverObject = NULL;
	serverObject = ctr_server_new(CtrStdObject, NULL);
	serverObject->link = CtrStdObject;
	ctr_internal_create_func(serverObject, ctr_build_string_from_cstring( CTR_DICT_NEW ), &ctr_server_new );
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
}

void init_embedded_gui_plugin() {
	begin();
}
