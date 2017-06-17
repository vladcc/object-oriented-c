/*
cclsString.h -- a C class example
As per the naming convention, cciString stands for "C class instance String" and
cclsString stands for "C class String". cciString receives the result of ccls_new(), while
cclsString is passed to ccls_new().
*/
/* v0.1 */
#ifndef CCLSSTRING_H
#define CCLSSTRING_H

#include "./cclass/cclass.h"

#define cclsString_base	char * str;\
						void (*print)(void * self);\
						void (*setTo)(void * self, const char * str);\
						const char * (*c_str)(void * self)

typedef struct cclsString_class {
	Cclass * cclass;	// mandatory pointer to the class descriptor
	cclsString_base;
} cclsString_class, * cciString;
/*
Description:
This class can be initialized to a string. Then it can print it's string
with print() or change it with setTo(). The this pointer has to be passed by 
hand (e.g. my_str->print(my_str)).
*/

extern const Cclass * cclsString;
/* cclsString is a pointer to the class descriptor defined in the class source file. */

/* 
Now the class can be used like so:

cciString my_string = ccls_new(cclsString, "text"); 
...code...
ccls_delete_null(my_string);

In the main program ccls_delete_null() is preferred over ccls_delete().
*/
#endif