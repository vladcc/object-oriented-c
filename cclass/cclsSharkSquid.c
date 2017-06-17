#include <stdio.h>
#include "./cclass/cclass.h"
#include "./cclass/err.h"
#include "cclsString.h"
#include "cclsAnimal.h"
#include "cclsShark.h"
#include "cclsSquid.h"
#include "cclsSharkSquid.h"

static void cclsSharkSquid_ctor(void * self, const void * args);
static void cclsSharkSquid_dtor(void * self);
static void cclsSharkSquid_printAnimalInfo(void * self);

static const Cclass cclsSharkSquid_descriptor = {
	"cclsSharkSquid",
	sizeof(cclsSharkSquid_class),
	cclsSharkSquid_ctor,
	cclsSharkSquid_dtor
};

const Cclass * cclsSharkSquid = &cclsSharkSquid_descriptor;

// method to override
static void (*cclsAnimal_printAnimalInfo)(void * self);

static void cclsSharkSquid_ctor(void * self, const void * args)
{
	edebug_print("#Called: %s\n", __func__);
	
	cciSharkSquid this = self;

	// fool the computer into thinking it's pointing to a cclsShark_class
	this->this_Shark = ccls_diamond_offset(this->this_Shark, cclsAnimal);
	
	// fool the computer into thinking it's pointing to a cclsSquid_class
	this->this_Squid = ccls_diamond_offset(this->this_Squid, cclsAnimal);
	
	const cclsSharkSquid_init * shsq_args = args;
	
	// initialize base class
	cclsAnimal->ctor(this, shsq_args);
	
	// initialze diamond classes
	cclsShark_init shark_args = {shsq_args->habitat, shsq_args->extremities, shsq_args->threat_level};
	cclsShark_diamond_ctor(this->this_Shark, &shark_args);
	
	cclsSquid_init squid_args = {shsq_args->habitat, shsq_args->extremities, shsq_args->iq};
	cclsSquid_diamond_ctor(this->this_Squid, &squid_args);
	
	// initialze own members
	this->hobby = ccls_new(cclsString, shsq_args->hobby);

	// save the address of the method to override
	cclsAnimal_printAnimalInfo = this->printAnimalInfo;
	
	// initialize methods; override method
	this->printAnimalInfo = cclsSharkSquid_printAnimalInfo;
	return;
}

static void cclsSharkSquid_dtor(void * self)
{
	edebug_print("#Called: %s\n", __func__);
	
	cciSharkSquid this = self;
	
	// destroy the base class
	cclsAnimal->dtor(this);
	
	// destroy diamond classes
	cclsShark_diamond_dtor(this->this_Shark);
	cclsSquid_diamond_dtor(this->this_Squid);
	
	// delete class members
	ccls_delete(this->hobby);
	return;
}

static void cclsSharkSquid_printAnimalInfo(void * self)
{
	cciSharkSquid this = self;
	
	// call base class method
	cclsAnimal_printAnimalInfo(this);
	
	// print info unique for this class
	printf("Hobby: ");
	this->hobby->print(this->hobby);
	
	// call Squid and Shark methods
	this->printSquidInfo(this->this_Squid);
	this->printSharkInfo(this->this_Shark);
	return;
}