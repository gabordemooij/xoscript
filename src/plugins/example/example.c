#include <stdio.h>
#include <stdlib.h>
#include "../../xo.h"

ctr_object* exampleObject;

void ctr_internal_example_init(void) {
	//init code here
}

ctr_object* ctr_example_new(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* instance = ctr_internal_create_object(CTR_OBJECT_TYPE_OTEX);
	instance->link = myself;
	return instance;
}

void begin() {
	ctr_internal_example_init();
	exampleObject = NULL;
	exampleObject = ctr_example_new(CtrStdObject, NULL);
	exampleObject->link = CtrStdObject;
	//create a constructor
	ctr_internal_create_func(exampleObject, CTR_STRINGOBJ( CTR_DICT_NEW ), &ctr_example_new );
	//add the Example plugin to the world
	ctr_internal_object_add_property(CtrStdWorld, CTR_STRINGOBJ( "Example" ), exampleObject, CTR_CATEGORY_PUBLIC_PROPERTY);
}
