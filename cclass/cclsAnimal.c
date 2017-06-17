#include <stdio.h>
#include "./cclass/cclass.h"
#include "./cclass/err.h"
#include "cclsString.h"
#include "cclsAnimal.h"

static void cclsAnimal_ctor(void * self, const void * args);
static void cclsAnimal_dtor(void * self);
static void cclsAnimal_printAnimalInfo(void * self);
static const char * cclsAnimal_getHabitat(void * self);
static int cclsAnimal_getExtremities(void *self);

static const Cclass cclsAnimal_descriptor = {
	"virtual_cclsAnimal",
	sizeof(cclsAnimal_class),
	cclsAnimal_ctor,
	cclsAnimal_dtor
};

const Cclass * cclsAnimal = &cclsAnimal_descriptor;

static void cclsAnimal_ctor(void * self, const void * args)
{
	edebug_print("#Called: %s\n", __func__);
	
	cclsAnimal_class * this = self;
	const cclsAnimal_init * animal_args = args;
	
	// initialize members
	this->habitat = ccls_new(cclsString, animal_args->habitat);
	this->extremities = animal_args->extremities;
	
	// initialize method pointers
	this->printAnimalInfo = cclsAnimal_printAnimalInfo;
	this->getHabitat = cclsAnimal_getHabitat;
	this->getExtremities = cclsAnimal_getExtremities;
	return;
}

static void cclsAnimal_dtor(void * self)
{
	edebug_print("#Called: %s\n", __func__);
	
	cclsAnimal_class * this = self;
	
	// destroy any contained objects
	ccls_delete(this->habitat);
	return;
}

static void cclsAnimal_printAnimalInfo(void * self)
{
	cclsAnimal_class * this = self;
	
	printf("Type: %s\n", ccls_type_of(this));
	printf("Habitat: ");
	this->habitat->print(this->habitat);
	printf("Extremities: %d\n", this->extremities);
	return;
}

static const char * cclsAnimal_getHabitat(void * self)
{
	cclsAnimal_class * this = self;
	return this->habitat->c_str(this->habitat);
}

static int cclsAnimal_getExtremities(void *self)
{
	cclsAnimal_class * this = self;
	return this->extremities;
}
