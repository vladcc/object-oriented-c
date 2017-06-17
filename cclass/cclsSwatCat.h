#ifndef CCLSSWATKAT_H
#define CCLSSWATKAT_H

#include "./cclass/cclass.h"
#include "cclsString.h"
#include "cclsAnimal.h"
#include "cclsCat.h"

#define cclsSwatCat_args	cclsCat_args;\
							const char * occupation;\
							const char * best_friend

typedef struct cclsSwatCat_init {
	cclsSwatCat_args;
} cclsSwatCat_init;	

#define cclsSwatCat_base	cclsCat_base;\
							cciString occupation;\
							cciString best_friend
							
typedef struct cclsSwatCat_class {
	Cclass * cclass;
	cclsSwatCat_base;
} cclsSwatCat_class, * cciSwatCat;

extern const Cclass * cclsSwatCat;
#endif