/* cclsString.c -- a C class example */
/* v0.1 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cclass.h"
#include "err.h"
#include "cclsString.h"

// method functions
static void cclsString_ctor(void * self, const void * args);
static void cclsString_dtor(void * self);
static void cclsString_print(void * self);
static void cclsString_setTo(void * self, const char * str);

// mandatory class descriptor definition
static const Cclass ccls_cclsString = {
	"ccls_string",		// class type
	sizeof(_cciString),	// class size in bytes
	cclsString_ctor,	// pointer to the constructor
	cclsString_dtor		// pointer to the destructor
};

// mandatory pointer to the class descriptor
const Cclass * _cclsString = &ccls_cclsString;

// implementation
static void cclsString_ctor(void * self, const void * args)
{
	/*	1. Set the function pointers to the class methods.
		2. Allocate memory for the string and copy it, or initialize to '\0'. */
	cciString ccip = self;
	
	ccip->print = cclsString_print;
	ccip->setTo = cclsString_setTo;
	
	const char * init_str = args;
	
	if (init_str)
	{
		ccip->str = emalloc(strlen(init_str) + 1);
		strcpy(ccip->str, init_str);
	}
	else
	{
		ccip->str = emalloc(1);
		ccip->str = '\0';
	}

	return;
}

static void cclsString_dtor(void * self)
{
	/*	1. Free the string memory.
		2. Null the member pointer. */
	cciString ccip = self;
	free(ccip->str);
	ccip->str = NULL;
	return;
}

static void cclsString_print(void * self)
{
	/* Print the string. */
	cciString ccip = self;
	puts(ccip->str);
	return;
}

static void cclsString_setTo(void * self, const char * str)
{
	/*	Change the string by calling the class destructor and then
		calling the constructor. */
	cclsString_dtor(self);
	cclsString_ctor(self, str);
	return;
}