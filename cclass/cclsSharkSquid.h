#ifndef CCLSHARKTOPUS_H
#define CCLSHARKTOPUS_H

#include "./cclass/cclass.h"
#include "cclsString.h"
#include "cclsAnimal.h"
#include "cclsShark.h"
#include "cclsSquid.h"

#define cclsSharkSquid_arg	const char * hobby

typedef struct cclsSharkSquid_init {
	cclsAnimal_args;
	cclsShark_args;
	cclsSquid_args;
	cclsSharkSquid_arg;
} cclsSharkSquid_init;

#define cclsSharkSquid_base	cciString hobby
						
typedef struct cclsSharkSquid_class {
	Cclass * cclass;
	cclsAnimal_base;
	dp_type this_Shark;	// diamond pointer
	cclsShark_base;
	dp_type this_Squid;	// diamond pointer
	cclsSquid_base;
	cclsSharkSquid_base;
} cclsSharkSquid_class, * cciSharkSquid;

extern const Cclass * cclsSharkSquid;
#endif