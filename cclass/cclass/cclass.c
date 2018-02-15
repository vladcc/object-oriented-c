/* cclass.c -- Base for OOP in plain C */
/* v1.2 */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cclass.h"
#include "err.h"

static char null_ptr_arg_err[] = "NULL pointer passed as argument";
static char no_ctor_err[] = "Cclass type < %s > has no constructor";
static char no_dtor_err[] = "Cclass type < %s > has no destructor";

void * ccls_new(const void * cclass, const void * args)
{	
	/*	1. Allocate space.
		2. Point the instance to it's descriptor.
		3. Call the constructor. */

	echeck_v(cclass, null_ptr_arg_err);
	
	const Cclass * ccls = cclass;
	void * ccinst = emalloc(ccls->size);
	
	*(const Cclass **)ccinst = ccls;
	echeck_v(ccls->ctor, no_ctor_err, ccls_type_of(ccinst));
	echeck_v(ccls->dtor, no_dtor_err, ccls_type_of(ccinst));
	
	ccls->ctor(ccinst, args);
	
	return ccinst;
}

void ccls_delete(void * ccinst)
{
	/*	1. Call the destructor.
		2. Free the memory occupied by the class instance. */
	echeck_v(ccinst, null_ptr_arg_err);
	
	Cclass * ccls = *((Cclass **)ccinst);
	
	echeck_v(ccls->dtor, no_dtor_err, ccls_type_of(ccinst));
	ccls->dtor(ccinst);
		
	free(ccinst);
	return;
}

size_t ccls_size_of(const void * ccinst)
{
	/* 1. Read the size filed of the class descriptor. */
	echeck_v(ccinst, null_ptr_arg_err);
	
	const Cclass * pccls = *((const Cclass **)ccinst);
	return pccls->size;
}

const char * ccls_type_of(const void * ccinst)
{
	/* 1. Read the type field of the class descriptor. */
	echeck_v(ccinst, null_ptr_arg_err);
	
	const Cclass * pccls = *((const Cclass **)ccinst);
	return pccls->type;
}

bool ccls_is_type_of(const void * ccinst, const char * str)
{
	/* 1. Compare the class type. */
	echeck_v(ccinst, null_ptr_arg_err);
	echeck_v(str, null_ptr_arg_err);
	
	return 0 == strcmp(ccls_type_of(ccinst), str);
}