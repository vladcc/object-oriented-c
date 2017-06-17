#include <stdio.h>
#include "./cclass/cclass.h"
#include "./cclass/err.h"
#include "cclsString.h"
#include "cclsAnimal.h"
#include "cclsSquid.h"

void cclsSquid_diamond_ctor(void * self, const void * args);
void cclsSquid_diamond_dtor(void * self);

static void cclsSquid_ctor(void * self, const void * args);
static void cclsSquid_dtor(void * self);
static void cclsSquid_printAnimalInfo(void * self);
static void cclsSquid_printSquidInfo(void * self);

static const Cclass cclsSquid_descriptor = {
	"cclsSquid",
	sizeof(cclsSquid_class),
	cclsSquid_ctor,
	cclsSquid_dtor
};

const Cclass * cclsSquid = &cclsSquid_descriptor;

// method to override
static void (*cclsAnimal_printAnimalInfo)(void * self);

void cclsSquid_diamond_ctor(void * self, const void * args)
{
	edebug_print("#Called: %s\n", __func__);
	
	cciSquid this = self;
	const cclsSquid_init * octo_args = args;
	
	// does not initialize the base class, only the members
	this->iq = octo_args->iq;
	
	// initialize methods
	this->printSquidInfo = cclsSquid_printSquidInfo;
	return;
}

void cclsSquid_diamond_dtor(void * self) 
{
	edebug_print("#Called: %s\n", __func__);
	return;
}

static void cclsSquid_ctor(void * self, const void * args)
{
	edebug_print("#Called: %s\n", __func__);
	
	cciSquid this = self;
	const cclsSquid_init * octo_args = args;
	
	// initialize base class
	cclsAnimal->ctor(this, octo_args);
	
	// save the address of the method to override
	cclsAnimal_printAnimalInfo = this->printAnimalInfo;
	
	// initialize members
	this->iq = octo_args->iq;
	
	// initialize methods; override the method from above
	this->printAnimalInfo = cclsSquid_printAnimalInfo;
	this->printSquidInfo = cclsSquid_printSquidInfo;
	return;
}

static void cclsSquid_dtor(void * self)
{
	edebug_print("#Called: %s\n", __func__);
	
	cciSquid this = self;
	
	// call base class destructor
	cclsAnimal->dtor(this);
	
	return;
}

static void cclsSquid_printAnimalInfo(void * self)
{
	cciSquid this = self;
	
	// call base class method
	cclsAnimal_printAnimalInfo(this);
	
	// call own method
	cclsSquid_printSquidInfo(this);
	return;
}

static void cclsSquid_printSquidInfo(void * self)
{
	cciSquid this = self;
	printf("IQ: %d\n", this->iq);
	return;
}