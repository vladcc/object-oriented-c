/* cclass.c -- Base for OOP in plain C */
/* v1.0 */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cclass.h"
#include "err.h"

void * ccls_new(const void * _cclass, const void * args)
{	
	/*	1. Allocate space.
		2. Point the instance to it's descriptor.
		3. Call the constructor. */
	if (NULL == _cclass)
		equit("NULL pointer passed to %s()", __func__);
	
	const Cclass * ccls = _cclass;
	void * p = emalloc(ccls->size);
	
	*(const Cclass **)p = ccls;

	if (ccls->ctor)
		ccls->ctor(p, args);
	else
		equit("Missing constructor of cclass type < %s >", ccls_type_of(p));
	
	return p;
}

void ccls_delete(void * _cclass)
{
	/*	1. Call the destructor.
		2. Free the memory occupied by the cclass.
		3. Set the cclass pointer to NULL. */
	if (NULL == _cclass)
		equit("NULL pointer passed to %s()", __func__);
	
	Cclass ** p = _cclass;
	if ((*p)->dtor)
		(*p)->dtor(_cclass);
	else
		equit("Missing destructor of cclass type < %s >", ccls_type_of(_cclass));
	
	free(_cclass);
	_cclass = NULL;
	return;
}

size_t ccls_size_of(const void * _cclass)
{
	/* Read the size filed of the class descriptor. */
	if (NULL == _cclass)
		equit("NULL pointer passed to %s()", __func__);
	
	const Cclass * cclsp = *((const Cclass **)_cclass);
	return cclsp->size;
}

const char * ccls_type_of(const void * _cclass)
{
	/* Read the type field of the class descriptor. */
	if (NULL == _cclass)
		equit("NULL pointer passed to %s()", __func__);
	
	const Cclass * cclsp = *((const Cclass **)_cclass);
	return cclsp->type;
}

bool ccls_is_type_of(const void * _cclass, const char * str)
{
	/* Compare the class type. */
	if (NULL == _cclass || NULL == str)
		equit("NULL pointer passed to %s()", __func__);
	
	return !strcmp(ccls_type_of(_cclass), str);
}