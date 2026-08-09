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
 * Copy the libctrexample.so to the /mods folder and
 * use in example.xo as:
 *
 * Program memory-management: 4.
 * {
 *    >> e := Example new.
 *    e set: ['ABC'].
 *    Out write: e get, stop.
 *    e push.
 * } start.
 * 
 * This plugin simply takes a text and pushes it into a memory block.
 */

// registration ID for plugin (explained below)
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
		rs->ptr = NULL;
	}
}

// Make a new method for your class-like object.
CTR_DEFINE_CLASS_OTEX(ctr_example_new, CTR_OBJECT_RESOURCE_EXAMPLE, ctr_example_destructor);

// Make a simple setter, this one uses a cast to string.
// It's often better to use copy2string (instead of cast2string)
// as your cast function, otherwise
// you might change the object of the user.
// Other casting functions are:
// - ctr_internal_copy2number
// - ctr_internal_copy2bool
// use the cast-equivalent if you don't change it (ctr_internal_cast2string).
// All cast2/copy2 functions can call user code.
CTR_DEFINE_SETTER_CAST(ctr_example_set_text, "mytext", ctr_internal_copy2string);

// Make a getter.
CTR_DEFINE_GETTER(ctr_example_get_text, "mytext");

// Do something with the external library,
// this is where the real thing happens.
ctr_object* ctr_example_push_to_memory(ctr_object* myself, ctr_argument* argumentList) {
	// If you are going to cast or call user code, pin
	// objects you created here to protect them from being GC'ed
	// with obj->info.sticky = 1; (in this case not needed, but just as a reminder).
	// Also don't forget to set the sticky=0 afterwards.
	// You may call user code with:
	// ctr_block_run(ctr_object* functionObj, ctr_arguments* args, NULL);.
	// User code may set CtrStdFlow.
	// If it is anything other then to CtrStdContinue,
	// break the loop if you're in one (it's probably CtrStdBreak or an error).
	ctr_object* mytext = ctr_internal_object_property(myself, "mytext", NULL);

	// If there is no property called "mytext", you get a None-object.
	// This is easy because you can return it to the user directly in some cases.
	if (mytext == CtrStdNil) return myself;

	// This is how you throw an exception
	if (myself->value.rvalue->ptr) {
		return ctr_error("Memory block is already full!!", 0);
	}

	// Pass to whatever library you want to connect.
	// To convert a String object to c-string use ctr_heap_allocate_cstring.
	// You can also allocate memory with: ctr_heap_allocate( size ).
	// Allocated memory must be freed with ctr_heap_free( ptr );
	// If you forget, XOScript will emit a warning.
	myself->value.rvalue->ptr = (char*) ctr_heap_allocate_cstring(mytext);
	printf("DEBUG: In memory block: %s \n", (char*)myself->value.rvalue->ptr);
	return myself;
}

// This gets called once the plugin is loaded:
void begin() {
	exampleObject = ctr_example_new(CtrStdObject, NULL);
	exampleObject->link = CtrStdObject;
	// Add the methods to the object, you may use CTR_DICT.. for localized method names.
	// CTR_STRINGOBJ sends both the string and its length, saves typing.
	ctr_internal_create_func(exampleObject, CTR_STRINGOBJ( "new" ), &ctr_example_new );
	ctr_internal_create_func(exampleObject, CTR_STRINGOBJ( "set:" ), &ctr_example_set_text );
	ctr_internal_create_func(exampleObject, CTR_STRINGOBJ( "get" ), &ctr_example_get_text );
	ctr_internal_create_func(exampleObject, CTR_STRINGOBJ( "push" ), &ctr_example_push_to_memory );
	// Add the Example plugin to the world, this puts it in global namespace.
	ctr_internal_object_add_property(CtrStdWorld, CTR_STRINGOBJ( "Example" ), exampleObject, CTR_CATEGORY_PUBLIC_PROPERTY);
}

/**
 * Some general notes:
 * - It's not needed to count arguments in your plugin function,
 *   XOScript always sends the correct number of arguments based on
 *   the method signature.
 * - To get the first argument: argumentList->object,
 * - To get the next: argumentList->next->object... and so on...
 * - Even if your function does not have arguments, always accept the argument
 *   you can just ignore it if you don't use it.
 * - There is no need to manage memory of ctr_objects, they are automatically
 *   under control of the garbage collector.
 * - If you create ctr_objects yourself within a function, and you call
 *   a user function (or perform a cast2string - which might call a user function),
 *   always pin your ctr_objects because, otherwise, the GC might delete them.
 * - Returning myself in a function allows the user to send additional
 *   messages to the object in one go.
 * - You may allocate memory with ctr_heap_allocate(), it is always cleared
 *   before usage, so it only contains zeroes.
 * - ctr_heap_alloc.. never fails.
 *
 * Registration of plugin.
 *
 * Most plugins will deal with external resources,
 * like a database, a network library or maybe a PDF lib or something...
 * So, anyway, something involving an external resource.
 * It is polite to register this as a separate number.
 * Use a resource id > 100 for non-core resources, i.e. everything.
 * Use id 99 for testing.
 * Plugin creators can notify me to register their
 * resource types in xo.h by sending a message.
 * By registering your plugin/resource, other plugins
 * may check and there will be no collisions.
 */
