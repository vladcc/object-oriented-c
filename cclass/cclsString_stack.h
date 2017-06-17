#ifndef CCLSSTRING_STACK_H
#define CCLSSTRING_STACK_H

#include "./cclass/cclass.h"

#define cclsString_stack_base	const char * str;\
								void (*print)(void * self);\
								void (*setTo)(void * self, const char * str);\
								const char * (*c_str)(void * self)

typedef struct cclsString_stack_class {
	Cclass * cclass;	// mandatory pointer to the class descriptor
	cclsString_stack_base;
} cclsString_stack_class, * cciString_stack;
/*
Description:
This class can remember a string pointer and print the string pointed to by the pointer.
*/

extern const Cclass * cclsString_stack;
/* cclsString_stack is a pointer to the class descriptor defined in the class source file. */

/* 
Use like so:

cciString my_string;
ccls_stack_new(my_string, cclsString_stack, "I'm on the stack!");
...code...
ccls_stack_delete(my_string);
*/
#endif