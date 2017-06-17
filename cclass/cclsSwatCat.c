#include <stdio.h>
#include "./cclass/cclass.h"
#include "./cclass/err.h"
#include "cclsString.h"
#include "cclsAnimal.h"
#include "cclsCat.h"
#include "cclsSwatCat.h"

static void cclsSwatCat_ctor(void * self, const void * args);
static void cclsSwatCat_dtor(void * self);
static void cclsSwatCat_printCatInfo(void * self);

static const Cclass cclsSwatCat_descriptor = {
	"cclsSwatCat",
	sizeof(cclsSwatCat_class),
	cclsSwatCat_ctor,
	cclsSwatCat_dtor
};

const Cclass * cclsSwatCat = &cclsSwatCat_descriptor;

// method to override
static void (*cclsCat_printCatInfo)(void * self);

static void cclsSwatCat_ctor(void * self, const void * args)
{
	edebug_print("#Called: %s\n", __func__);
	
	cciSwatCat this = self;
	const cclsSwatCat_init * swat_cat_args = args;
	
	// initialize base class
	const cclsCat_init * cat_args = args;
	cclsCat->ctor(this, cat_args);
	
	// save method's address
	cclsCat_printCatInfo = this->printCatInfo;
	
	// initialize members
	this->occupation = ccls_new(cclsString, swat_cat_args->occupation);
	this->best_friend = ccls_new(cclsString, swat_cat_args->best_friend);
	
	// initialize methods; override method from above
	this->printCatInfo = cclsSwatCat_printCatInfo;
	return;
}

static void cclsSwatCat_dtor(void * self)
{
	edebug_print("#Called: %s\n", __func__);
	
	cciSwatCat this = self;
	
	// call base class destructor
	cclsCat->dtor(this);
	
	// delete any contained objects
	ccls_delete(this->occupation);
	ccls_delete(this->best_friend);
	return;
}

static void cclsSwatCat_printCatInfo(void * self)
{
	cciSwatCat this = self;
	
	// use the overrided method by calling it
	cclsCat_printCatInfo((cciCat)this);
	
	printf("Occupation: ");
	this->occupation->print(this->occupation);
	printf("Best friend: ");
	this->best_friend->print(this->best_friend);
	return;
}