#include <stdio.h>
#include <stdlib.h>
#include "../../xo.h"

/**
 * Example plugin
 *
 * Creating an example plugin is really easy.
 * See the makefiles how to build. Build from root folder with:
 *
 * NAME="example" PACKAGE="example" make -f makefile.obsd plugin-clean
 * NAME="example" PACKAGE="example" make -f makefile.obsd plugin
 *
 * And use in example.xo as:
 *
 * Program memory-management: 4.
 * {
 *    >> e := Example new.
 *    e set: ['ABC'].
 *    Out write: e get, stop.
 *    e push.
 * } start.
 * 
 * The inline comments explain the rest...
 */

/**
 * Most plugins will deal with external resources,
 * like a database, a network library or maybe a PDF lib or something...
 * So, anyway, something involving an external resource.
 * It is polite to register this as a separate number.
 * Use a resource id > 100 for non core resources.
 * Use id 99 for testing.
 */
#define CTR_OBJECT_RESOURCE_EXAMPLE 99

ctr_object* exampleObject;

// Make a destructor, this gets called once the
// garbage collector deletes the object.
// That's why we use Program memory-management: 4,
// to test: it sweeps every cycle.
void ctr_example_destructor(ctr_resource* rs) {
	if (rs->ptr) {
		printf("DEBUG: destructor called.\n");
		ctr_heap_free(rs->ptr);
	}
}

// Make a new method for your class-like object
CTR_DEFINE_CLASS_OTEX(ctr_example_new, CTR_OBJECT_RESOURCE_EXAMPLE, ctr_example_destructor);

// make a simple setter, this one uses a cast to string
CTR_DEFINE_SETTER_CAST(ctr_example_set_text, "mytext", ctr_internal_copy2string);

// make a getter
CTR_DEFINE_GETTER(ctr_example_get_text, "mytext");

// do something with the external library
ctr_object* ctr_example_push_to_memory(ctr_object* myself, ctr_argument* argumentList) {
	// if you are going to cast or call user code, pin
	// objects you created here to protect them from being GC'ed
	// with obj->info.sticky = 1; (in this case not needed, but just as a reminder)
	// also don't forget to set the sticky=0 afterwards.
	ctr_object* mytext = ctr_internal_object_property(myself, "mytext", NULL);

	// If there is no such property, you get a None-object
	// this is easy because you can return it to the user directly in some cases.
	if (mytext == CtrStdNil) return myself;

	// Pass to whatever library you want to connect
	myself->value.rvalue->ptr = (char*) ctr_heap_allocate_cstring(mytext);
	printf("DEBUG: In memory block: %s \n", (char*)myself->value.rvalue->ptr);
	return myself;
}

// This gets called once the plugin is loaded:
void begin() {
	exampleObject = ctr_example_new(CtrStdObject, NULL);
	exampleObject->link = CtrStdObject;
	// Add the methods to the object, you may use CTR_DICT.. for localized method names
	ctr_internal_create_func(exampleObject, CTR_STRINGOBJ( "new" ), &ctr_example_new );
	ctr_internal_create_func(exampleObject, CTR_STRINGOBJ( "set:" ), &ctr_example_set_text );
	ctr_internal_create_func(exampleObject, CTR_STRINGOBJ( "get" ), &ctr_example_get_text );
	ctr_internal_create_func(exampleObject, CTR_STRINGOBJ( "push" ), &ctr_example_push_to_memory );
	// Add the Example plugin to the world
	ctr_internal_object_add_property(CtrStdWorld, CTR_STRINGOBJ( "Example" ), exampleObject, CTR_CATEGORY_PUBLIC_PROPERTY);
}
