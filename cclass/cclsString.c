/* cclsString.c -- a C class example */
/* v0.2 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./cclass/cclass.h"
#include "./cclass/err.h"
#include "cclsString.h"

// method functions
static void cclsString_ctor(void * self, const void * args);
static void cclsString_dtor(void * self);
static void cclsString_print(void * self);
static void cclsString_setTo(void * self, const char * str);
static const char * cclsString_cstr(void * self);

// mandatory class descriptor definition
static const Cclass cclsString_descriptor = {
	"cclsString",				// class type
	sizeof(cclsString_class),	// class size in bytes
	cclsString_ctor,			// pointer to the constructor
	cclsString_dtor				// pointer to the destructor
};

// mandatory pointer to the class descriptor
const Cclass * cclsString = &cclsString_descriptor;

// implementation
static void cclsString_ctor(void * self, const void * args)
{
	/*	1. Allocate memory for the string and copy it, or initialize to '\0'. 
		2. Set the function pointers to the class methods. */
	cciString this = self;
	
	const char * init_str = args;
	
	// initialize members
	if (init_str)
	{
		this->str = emalloc(strlen(init_str) + 1);
		strcpy(this->str, init_str);
	}
	else
	{
		this->str = emalloc(1);
		this->str = '\0';
	}

	// initialize method pointers
	this->print = cclsString_print;
	this->setTo = cclsString_setTo;
	this->c_str = cclsString_cstr;
	
	return;
}

static void cclsString_dtor(void * self)
{
	/*	1. Free the string memory. */
	cciString this = self;
	efree_null(this->str);
	return;
}

static void cclsString_print(void * self)
{
	/* 1. Print the string. */
	cciString this = self;
	puts(this->str);
	return;
}

static void cclsString_setTo(void * self, const char * str)
{
	/*	1. Change the string by calling the class destructor and then
		calling the constructor again. */
	cclsString_dtor(self);
	cclsString_ctor(self, str);
	return;
}

static const char * cclsString_cstr(void * self)
{
	/*	1. Return a pointer to the string data. */
	cciString this = self;
	return this->str;
}