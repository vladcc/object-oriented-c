#include <stdio.h>
#include "./cclass/cclass.h"
#include "./cclass/err.h"
#include "cclsString.h"
#include "cclsAnimal.h"
#include "cclsCat.h"

static void cclsCat_ctor(void * self, const void * args);
static void cclsCat_dtor(void * self);
static void cclsCat_printCatInfo(void * self);

static const Cclass cclsCat_descriptor = {
	"cclsCat",
	sizeof(cclsCat_class),
	cclsCat_ctor,
	cclsCat_dtor
};

const Cclass * cclsCat = &cclsCat_descriptor;

static void cclsCat_ctor(void * self, const void * args)
{
	edebug_print("#Called: %s\n", __func__);
	
	cciCat this = self;
	const cclsCat_init * cat_args = args;
	
	// initialize base class
	const cclsAnimal_init * animal_args = args;
	cclsAnimal->ctor(this, animal_args);
	
	// initialize members
	this->name = ccls_new(cclsString, cat_args->name);
	this->menace_factor = ccls_new(cclsString, cat_args->menace_factor);
	
	// initialze method pointers
	this->printCatInfo = cclsCat_printCatInfo;
	return;
}

static void cclsCat_dtor(void * self)
{
	edebug_print("#Called: %s\n", __func__);
	
	cciCat this = self;
	
	// call base class destructor
	cclsAnimal->dtor(this);
	
	// delete any contained objects
	ccls_delete(this->name);
	ccls_delete(this->menace_factor);
	return;
}

static void cclsCat_printCatInfo(void * self)
{
	cciCat this = self;
	
	this->printAnimalInfo(this);
	printf("Name: ");
	this->name->print(this->name);
	printf("Menace factor: ");
	this->menace_factor->print(this->menace_factor);
	return;
}