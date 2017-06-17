#ifndef CCLSCAT_H
#define CCLSCAT_H

#include "./cclass/cclass.h"
#include "cclsString.h"
#include "cclsAnimal.h"

#define cclsCat_args	cclsAnimal_args;\
						const char * name;\
						const char * menace_factor

typedef struct cclsCat_init {
	cclsCat_args;
} cclsCat_init;

#define cclsCat_base	cclsAnimal_base;\
						cciString name;\
						cciString menace_factor;\
						void (*printCatInfo)(void * self)

typedef struct cclsCat_class {
	Cclass * cclass;
	cclsCat_base;
} cclsCat_class, * cciCat;

extern const Cclass * cclsCat;
#endif