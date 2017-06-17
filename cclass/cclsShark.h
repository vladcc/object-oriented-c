#ifndef CCLSSHARK_H
#define CCLSSHARK_H

#include "./cclass/cclass.h"
#include "cclsString.h"
#include "cclsAnimal.h"

#define cclsShark_args	const char * threat_level

typedef struct cclsShark_init {
	cclsAnimal_args;
	cclsShark_args;
} cclsShark_init;

#define cclsShark_base	cciString threat_level;\
						void (*printSharkInfo)(void * self)
						
typedef struct cclsShark_class {
	Cclass * cclass;
	cclsAnimal_base;
	cclsShark_base;
} cclsShark_class, * cciShark;

extern const Cclass * cclsShark;

void cclsShark_diamond_ctor(void * self, const void * args);
void cclsShark_diamond_dtor(void * self);
#endif