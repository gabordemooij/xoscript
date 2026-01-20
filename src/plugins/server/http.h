#include "ccgi/ccgi.h"

ctr_object* ctr_request_string(ctr_object* myself, ctr_argument* argumentList, CGI_varlist* varlist);
ctr_object* ctr_request_array(ctr_object* myself, ctr_argument* argumentList, CGI_varlist* varlist);
ctr_object* ctr_request_get_string(ctr_object* myself, ctr_argument* argumentList);
ctr_object* ctr_request_get_array(ctr_object* myself, ctr_argument* argumentList);
ctr_object* ctr_request_post_string(ctr_object* myself, ctr_argument* argumentList);
ctr_object* ctr_request_post_array(ctr_object* myself, ctr_argument* argumentList);
ctr_object* ctr_request_cookie_string(ctr_object* myself, ctr_argument* argumentList);
ctr_object* ctr_request_cookie_array(ctr_object* myself, ctr_argument* argumentList);
ctr_object* ctr_request_file(ctr_object* myself, ctr_argument* argumentList);
void begin_http();

