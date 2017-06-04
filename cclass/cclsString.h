/*
cclsString.h -- a C class example
As per the naming convention, cciString stands for "C class instance String" and
_cclsString stands for "C class String". cciString receives the result of ccls_new(), while
_cclsString is passed to ccls_new().
*/
/* v0.1 */
#ifndef CCLSSTRING_H
#define CCLSSTRING_H

#include "cclass.h"

typedef struct _cciString_struct {
	// members
	Cclass * _cclass;	// mandatory pointer to the class descriptor
	char * str;			// pointer to the string
	// methods
	void (*print)(void * self);
	void (*setTo)(void * self, const char * str);
} _cciString;
/*
Description:
This class can be initialized to a string. Then it can print it's string
with print() or change it with setTo(). That's it. It does nothing fancy.
When calling any method working with the class members, a pointer to the 
calling instance must be passed, hence the void * self.
*/

typedef _cciString * cciString;
/* cciString is used to get the returned value of ccls_new(). */

extern const Cclass * _cclsString;
/* _cclsString is a pointer to the class descriptor defined in the class source file. */

/* 
Now the class can be used like so:

cciString my_string = ccls_new(_cclsString, "text"); 
...code...
ccls_delete(my_string);
*/
#endif