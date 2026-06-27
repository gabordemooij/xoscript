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

char* CtrCurlBuffer;
size_t CtrCurlBufferSize;
size_t CtrCurlBytesRead;
size_t ctr_curl_write_callback(char* ptr, size_t size, size_t nmemb, void *userdata) {
	size_t len = (size * nmemb);
	size_t required_size = len + CtrCurlBytesRead;
	if (required_size > CtrCurlBufferSize) {
		CtrCurlBuffer = ctr_heap_reallocate(CtrCurlBuffer, required_size + 1); //extra room for NUL-byte
		CtrCurlBufferSize = required_size;
	}
	memcpy(CtrCurlBuffer+CtrCurlBytesRead, ptr, len);
	CtrCurlBytesRead += len;
	return len;
}

/**
 * @def
 * [ Net ] post: [ String ] to: [ String ]
 *
 * @test661
 */
ctr_object* ctr_network_basic_text_send(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* result;
	char* message_str = NULL;
	char* destination = ctr_heap_allocate_cstring(ctr_internal_cast2string(argumentList->next->object));
	CURL* curl;
	CURLcode res;
	CtrCurlBuffer = ctr_heap_allocate(10);
	CtrCurlBufferSize = 10;
	CtrCurlBytesRead = 0;
	if (!CtrNetworkConnectedFlag) {
		curl_global_init(CURL_GLOBAL_DEFAULT);
	}
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, destination);
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
		result = ctr_build_string_from_cstring(CtrCurlBuffer);
	}
	CtrCurlBytesRead = 0;
	if (CtrCurlBufferSize) {
		ctr_heap_free(CtrCurlBuffer);
		CtrCurlBuffer = NULL;
		CtrCurlBufferSize = 0;
	}
	ctr_heap_free(destination);
	if (message_str) {
		ctr_heap_free(message_str);
	}
	return result;
}

/**
 * @def
 * [ Net ] get: [ String ]
 *
 * @test653
 */
ctr_object* ctr_network_get(ctr_object* myself, ctr_argument* argumentList) {
	ctr_argument a;
	ctr_argument u;
	a.object = CtrStdNil;
	u.object = argumentList->object;
	a.next = &u;
	u.next = NULL;
	return ctr_network_basic_text_send(myself, &a);
}


void begin_net() {
	CtrCurlObject = ctr_network_new(CtrStdObject, NULL);
	CtrCurlObject->link = CtrStdObject;
	ctr_internal_create_func(CtrCurlObject, CTR_STRINGOBJ( CTR_DICT_NEW ), &ctr_network_new );
	ctr_internal_create_func(CtrCurlObject, CTR_STRINGOBJ( CTR_DICT_HTTP_REQUEST_POST_TO_SET ), &ctr_network_basic_text_send );
	ctr_internal_create_func(CtrCurlObject, CTR_STRINGOBJ( CTR_DICT_HTTP_REQUEST_GET_SET ), &ctr_network_get );
	ctr_internal_object_add_property(CtrStdWorld, CTR_STRINGOBJ( CTR_DICT_NETWORK_OBJECT ), CtrCurlObject, CTR_CATEGORY_PUBLIC_PROPERTY);	
}

