#include <stdio.h>
#include "./cclass/cclass.h"
#include "./cclass/err.h"
#include "cclsString.h"
#include "cclsManBearPug.h"

/* --------------------  cclsMan  -------------------- */
static void cclsMan_ctor(void * self, const void * args);
static void cclsMan_dtor(void * self);
static void cclsMan_walk(void * self);
static void cclsMan_printManInfo(void * self);

static const Cclass cclsMan_descriptor = {
	"cclsMan",
	sizeof(cclsMan_class),
	cclsMan_ctor,
	cclsMan_dtor
};

const Cclass * cclsMan = &cclsMan_descriptor;

static void cclsMan_ctor(void * self, const void * args)
{
	edebug_print("#Called: %s\n", __func__);
	
	cciMan this = self;
	const cclsMan_init * man_init = args;
	
	// initialize members
	this->name = ccls_new(cclsString, man_init->name);
	this->height = man_init->height;
	
	// initialize methods
	this->walk = cclsMan_walk;
	this->printManInfo = cclsMan_printManInfo;
	return;
}

static void cclsMan_dtor(void * self)
{
	edebug_print("#Called: %s\n", __func__);
	cciMan this = self;
	
	// delete contained objects
	ccls_delete(this->name);
	return;
}

static void cclsMan_walk(void * self)
{
	puts("Walks on two legs");
	return;
}

static void cclsMan_printManInfo(void * self)
{
	cciMan this = self;
	
	printf("Name: ");
	this->name->print(this->name);
	printf("Height: %d cm\n", this->height);
	return;
}
/* -------------------- /cclsMan  -------------------- */


/* --------------------  cclsBear  -------------------- */
static void cclsBear_ctor(void * self, const void * args);
static void cclsBear_dtor(void * self);
static void cclsBear_roar(void * self);
static void cclsBear_printBearInfo(void * self);

static const Cclass cclsBear_descriptor = {
	"cclsBear",
	sizeof(cclsBear_class),
	cclsBear_ctor,
	cclsBear_dtor
};

const Cclass * cclsBear = &cclsBear_descriptor;

static void cclsBear_ctor(void * self, const void * args)
{
	edebug_print("#Called: %s\n", __func__);
	
	cciBear this = self;
	const cclsBear_init * bear_init = args;

	// initialize members
	this->weight = bear_init->weight;
	this->hair = ccls_new(cclsString, bear_init->hair);
	
	// initialize methods
	this->roar = cclsBear_roar;
	this->printBearInfo = cclsBear_printBearInfo;
	return;
}

static void cclsBear_dtor(void * self)
{
	edebug_print("#Called: %s\n", __func__);
	
	cciBear this = self;
	// delete contained objects
	ccls_delete(this->hair);
	return;
}

static void cclsBear_roar(void * self)
{
	puts("Roars scaringly");
	return;
}

static void cclsBear_printBearInfo(void * self)
{
	cciBear this = self;
	printf("Weight: %d kg\n", this->weight);
	printf("Hair: ");
	this->hair->print(this->hair);
	return;
}
/* -------------------- /cclsBear  -------------------- */


/* --------------------  cclsPug  -------------------- */
static void cclsPug_ctor(void * self, const void * args);
static void cclsPug_dtor(void * self);
static void cclsPug_snort(void * self);

static const Cclass cclsPug_descriptor = {
	"cclsPug",
	sizeof(cclsPug_class),
	cclsPug_ctor,
	cclsPug_dtor
};

const Cclass * cclsPug = &cclsPug_descriptor;

static void cclsPug_ctor(void * self, const void * args)
{
	edebug_print("#Called: %s\n", __func__);
	
	cciPug this = self;
	
	// initialize methods
	this->snort = cclsPug_snort;
	return;
}

static void cclsPug_dtor(void * self)
{
	edebug_print("#Called: %s\n", __func__);
	return;
}

static void cclsPug_snort(void * self)
{
	puts("Snorts profusely");
	return;
}
/* -------------------- /cclsPug  -------------------- */


/* --------------------  cclsManBearPug  -------------------- */
static void cclsManBearPug_ctor(void * self, const void * args);
static void cclsManBearPug_dtor(void * self);
static void cclsManBearPug_beScary(void * self);

static const Cclass cclsManBearPug_descriptor = {
	"cclsManBearPug",
	sizeof(cclsManBearPug_class),
	cclsManBearPug_ctor,
	cclsManBearPug_dtor
};

const Cclass * cclsManBearPug = &cclsManBearPug_descriptor;

static void cclsManBearPug_ctor(void * self, const void * args)
{
	edebug_print("#Called: %s\n", __func__);
	
	cciManBearPug this = self;
	const cclsManBearPug_init * mbp_init = args;
	
	// fool the computer into thinking it's pointing to valid class objects
	this->this_Man = ccls_mult_offset(this->this_Man);
	this->this_Bear = ccls_mult_offset(this->this_Bear);
	this->this_Pug = ccls_mult_offset(this->this_Pug);
	
	// call constructors
	const cclsMan_init man_init = {mbp_init->name, mbp_init->height};
	cclsMan->ctor(this->this_Man, &man_init);
	
	const cclsBear_init bear_init = {mbp_init->weight, mbp_init->hair};
	cclsBear->ctor(this->this_Bear, &bear_init);
	
	const cclsPug_init pug_init = {NULL};
	cclsPug->ctor(this->this_Pug, &pug_init);
	
	// initialize methods
	this->beScary = cclsManBearPug_beScary;
	return;
}

static void cclsManBearPug_dtor(void * self)
{
	edebug_print("#Called: %s\n", __func__);
	
	cciManBearPug this = self;
	
	// call destructors
	cclsMan->dtor(this->this_Man);
	cclsBear->dtor(this->this_Bear);
	cclsPug->dtor(this->this_Pug);
	return;
}

static void cclsManBearPug_beScary(void * self)
{
	cciManBearPug this = self;
	
	this->printManInfo(this->this_Man);
	this->printBearInfo(this->this_Bear);
	
	this->walk(this->this_Man);
	this->roar(this->this_Bear);
	this->snort(this->this_Pug);
	return;
}
/* -------------------- /cclsManBearPug  -------------------- */