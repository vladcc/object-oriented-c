#ifndef CCLSANIMAL_H
#define CCLSANIMAL_H

#include "./cclass/cclass.h"
#include "cclsString.h"

#define cclsAnimal_args const char * habitat;\
						int extremities

typedef struct cclsAnimal_init {
	cclsAnimal_args;
} cclsAnimal_init;

#define cclsAnimal_base	cciString habitat;\
						int extremities;\
						void (*printAnimalInfo)(void * self);\
						const char * (*getHabitat)(void * self);\
						int (*getExtremities)(void *self)
						
/* printAnimalInfo() is intended as a virtual method */
						
typedef struct cclsAnimal_class {
	Cclass * cclass;
	cclsAnimal_base;
} cclsAnimal_class;	// no cciAnimal; cclsAnimal is a virtual base class

extern const Cclass * cclsAnimal;
#endif