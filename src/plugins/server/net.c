#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "net.h"
#include <server.h>
#include "../../xo.h"

ctr_object* CtrCurlObject;

int CtrNetworkConnectedFlag = 0;

ctr_object* ctr_network_new(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* instance = ctr_internal_create_object(CTR_OBJECT_TYPE_OTEX);
	instance->link = myself;
	return instance;
}

char* CtrMediaCurlBuffer;
size_t CtrMediaCurlBufferSize;
size_t CtrMediaCurlBytesRead;
size_t ctr_curl_write_callback(char* ptr, size_t size, size_t nmemb, void *userdata) {
	size_t len = (size * nmemb);
	size_t required_size = len + CtrMediaCurlBytesRead;
	if (required_size > CtrMediaCurlBufferSize) {
		CtrMediaCurlBuffer = ctr_heap_reallocate(CtrMediaCurlBuffer, required_size);
		CtrMediaCurlBufferSize = required_size;
	}
	memcpy(CtrMediaCurlBuffer+CtrMediaCurlBytesRead, ptr, len);
	CtrMediaCurlBytesRead += len;
	return len;
}

ctr_object* ctr_network_basic_text_send(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* result;
	char* message_str = NULL;
	char* destination = ctr_heap_allocate_cstring(ctr_internal_cast2string(argumentList->next->object));
	CURL* curl;
	CURLcode res;
	CtrMediaCurlBuffer = ctr_heap_allocate(10);
	CtrMediaCurlBufferSize = 10;
	CtrMediaCurlBytesRead = 0;
	if (!CtrNetworkConnectedFlag) {
		curl_global_init(CURL_GLOBAL_DEFAULT);
	}
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, destination);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	if (argumentList->object != CtrStdNil) {
		message_str = ctr_heap_allocate_cstring(ctr_internal_cast2string(argumentList->object));
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message_str);
	}
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &ctr_curl_write_callback);
	res = curl_easy_perform(curl);
	if(res != CURLE_OK) {
		result = ctr_error((char*)curl_easy_strerror(res), 0);
	} else {
		curl_easy_cleanup(curl);
		result = ctr_build_string_from_cstring(CtrMediaCurlBuffer);
	}
	CtrMediaCurlBytesRead = 0;
	if (CtrMediaCurlBufferSize) {
		ctr_heap_free(CtrMediaCurlBuffer);
		CtrMediaCurlBuffer = NULL;
		CtrMediaCurlBufferSize = 0;
	}
	ctr_heap_free(destination);
	if (message_str) {
		ctr_heap_free(message_str);
	}
    return result;
}

void begin_net() {
	CtrCurlObject = ctr_network_new(CtrStdObject, NULL);
	CtrCurlObject->link = CtrStdObject;
	ctr_internal_create_func(CtrCurlObject, ctr_build_string_from_cstring( "new" ), &ctr_network_new );
	ctr_internal_create_func(CtrCurlObject, ctr_build_string_from_cstring( "post:to:" ), &ctr_network_basic_text_send );
	ctr_internal_object_add_property(CtrStdWorld, ctr_build_string_from_cstring( "Net" ), CtrCurlObject, CTR_CATEGORY_PUBLIC_PROPERTY);	
}

