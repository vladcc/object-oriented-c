#ifndef CCLSSQUID_H
#define CCLSSQUID_H

#include "./cclass/cclass.h"
#include "cclsString.h"
#include "cclsAnimal.h"

#define cclsSquid_args	int iq

typedef struct cclsSquid_init {
	cclsAnimal_args;
	cclsSquid_args;
} cclsSquid_init;

#define cclsSquid_base	int iq;\
						void (*printSquidInfo)(void * self)
						
typedef struct cclsSquid_class {
	Cclass * cclass;
	cclsAnimal_base;
	cclsSquid_base;
} cclsSquid_class, * cciSquid;

extern const Cclass * cclsSquid;

void cclsSquid_diamond_ctor(void * self, const void * args);
void cclsSquid_diamond_dtor(void * self);
#endif