#include <stdio.h>
#include "./cclass/cclass.h"
#include "./cclass/err.h"
#include "cclsString.h"
#include "cclsAnimal.h"
#include "cclsShark.h"

void cclsShark_diamond_ctor(void * self, const void * args);
void cclsShark_diamond_dtor(void * self);

static void cclsShark_ctor(void * self, const void * args);
static void cclsShark_dtor(void * self);
static void cclsShark_printAnimalInfo(void * self);
static void cclsShark_printSharkInfo(void * self);

static const Cclass cclsShark_descriptor = {
	"cclsShark",
	sizeof(cclsShark_class),
	cclsShark_ctor,
	cclsShark_dtor
};

const Cclass * cclsShark = &cclsShark_descriptor;

// method to override
static void (*cclsAnimal_printAnimalInfo)(void * self);

void cclsShark_diamond_ctor(void * self, const void * args)
{
	edebug_print("#Called: %s\n", __func__);
	
	cciShark this = self;
	const cclsShark_init * shark_args = args;
	
	// initialize members
	this->threat_level = ccls_new(cclsString, shark_args->threat_level);
	
	// initialize methods
	this->printSharkInfo = cclsShark_printSharkInfo;
	return;
}

void cclsShark_diamond_dtor(void * self)
{
	edebug_print("#Called: %s\n", __func__);
	
	// delete any contained objects
	cciShark this = self;
	ccls_delete(this->threat_level);
	return;
}

static void cclsShark_ctor(void * self, const void * args)
{
	edebug_print("#Called: %s\n", __func__);
	
	cciShark this = self;
	const cclsShark_init * shark_args = args;
	
	// initialize base class
	const cclsAnimal_init * animal_args = args;
	cclsAnimal->ctor(this, animal_args);
	
	// save the address of the method to override
	cclsAnimal_printAnimalInfo = this->printAnimalInfo;
	
	// initialize members
	this->threat_level = ccls_new(cclsString, shark_args->threat_level);
	
	// initialize methods; override the method from above
	this->printAnimalInfo = cclsShark_printAnimalInfo;
	this->printSharkInfo = cclsShark_printSharkInfo;
	return;
}

static void cclsShark_dtor(void * self)
{
	edebug_print("#Called: %s\n", __func__);
	
	cciShark this = self;
	
	// call base class destructor
	cclsAnimal->dtor(this);
	
	// delete any contained objects
	ccls_delete(this->threat_level);
	
	return;
}

static void cclsShark_printAnimalInfo(void * self)
{
	cciShark this = self;
	
	// call base class method
	cclsAnimal_printAnimalInfo(this);
	
	// call own method
	cclsShark_printSharkInfo(this);
	return;
}

static void cclsShark_printSharkInfo(void * self)
{
	cciShark this = self;
	
	printf("Threat level: ");
	this->threat_level->print(this->threat_level);
	return;
}