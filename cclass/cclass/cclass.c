/* cclass.c -- Base for OOP in plain C */
/* v1.1 */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cclass.h"
#include "err.h"

void * ccls_new(const void * cclass, const void * args)
{	
	/*	1. Allocate space.
		2. Point the instance to it's descriptor.
		3. Call the constructor. */
	if (NULL == cclass)
		equit("NULL pointer passed to %s()", __func__);
	
	const Cclass * ccls = cclass;
	void * ccinst = emalloc(ccls->size);
	
	*(const Cclass **)ccinst = ccls;

	if (ccls->ctor)
		ccls->ctor(ccinst, args);
	else
		equit("Cclass type < %s > has no constructor", ccls_type_of(ccinst));
	
	return ccinst;
}

void ccls_delete(void * ccinst)
{
	/*	1. Call the destructor.
		2. Free the memory occupied by the class instance. */
	if (NULL == ccinst)
		equit("NULL pointer passed to %s()", __func__);
	
	Cclass * pccls = *((Cclass **)ccinst);
	if (pccls->dtor)
		pccls->dtor(ccinst);
	else
		equit("Cclass type < %s > has no destructor", ccls_type_of(ccinst));
	
	free(ccinst);
	return;
}

size_t ccls_size_of(const void * ccinst)
{
	/* 1. Read the size filed of the class descriptor. */
	if (NULL == ccinst)
		equit("NULL pointer passed to %s()", __func__);
	
	const Cclass * pccls = *((const Cclass **)ccinst);
	return pccls->size;
}

const char * ccls_type_of(const void * ccinst)
{
	/* 1. Read the type field of the class descriptor. */
	if (NULL == ccinst)
		equit("NULL pointer passed to %s()", __func__);
	
	const Cclass * pccls = *((const Cclass **)ccinst);
	return pccls->type;
}

bool ccls_is_type_of(const void * ccinst, const char * str)
{
	/* 1. Compare the class type. */
	if (NULL == ccinst || NULL == str)
		equit("NULL pointer passed to %s()", __func__);
	
	return !strcmp(ccls_type_of(ccinst), str);
}