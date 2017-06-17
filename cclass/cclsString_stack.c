/* cclsString_stack.c -- a C class example */
/* v0.1 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./cclass/cclass.h"
#include "./cclass/err.h"
#include "cclsString_stack.h"

// method functions
static void cclsString_stack_ctor(void * self, const void * args);
static void cclsString_stack_dtor(void * self);
static void cclsString_stack_print(void * self);
static void cclsString_stack_setTo(void * self, const char * str);
static const char * cclsString_stack_cstr(void * self);

// mandatory class descriptor definition
static const Cclass cclsString_stack_descriptor = {
	"cclsString_stack",				// class type
	sizeof(cclsString_stack_class),	// class size in bytes
	cclsString_stack_ctor,			// pointer to the constructor
	cclsString_stack_dtor			// pointer to the destructor
};

// mandatory pointer to the class descriptor
const Cclass * cclsString_stack = &cclsString_stack_descriptor;

// implementation
static void cclsString_stack_ctor(void * self, const void * args)
{
	edebug_print("#Called: %s\n", __func__);
	
	/*	1. Save the string pointer.
		2. Initialize method pointers. */
	cciString_stack this = self;
	
	const char * init_str = args;
	
	// initialize members
	this->str = init_str;
	
	// initialze method pointers
	this->print = cclsString_stack_print;
	this->setTo = cclsString_stack_setTo;
	this->c_str = cclsString_stack_cstr;
	
	return;
}

static void cclsString_stack_dtor(void * self)
{
	edebug_print("#Called: %s\n", __func__);
	// everything's on the stack; nothing to free
	return;
}

static void cclsString_stack_print(void * self)
{
	/* 1. Print the string. */
	cciString_stack this = self;
	puts(this->str);
	return;
}

static void cclsString_stack_setTo(void * self, const char * str)
{
	/* 1. Change the pointer value */
	
	cciString_stack this = self;
	this->str = str;
	return;
}

static const char * cclsString_stack_cstr(void * self)
{
	/* 1. Return the string pointer. */
	cciString_stack this = self;
	return this->str;
}