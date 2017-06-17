#ifndef CCLSMANBEARPUG_H
#define CCLSMANBEARPUG_H

#include "./cclass/cclass.h"
#include "cclsString.h"

/* --------------------  cclsMan  -------------------- */
#define cclsMan_args	const char * name;\
						int height
						
typedef struct cclsMan_init {
	cclsMan_args;
} cclsMan_init;

#define cclsMan_base	cciString name;\
						int height;\
						void (*walk)(void * self);\
						void (*printManInfo)(void * self)
						
typedef struct cclsMan_class {
	Cclass * cclass;
	cclsMan_base;
} cclsMan_class, * cciMan;

extern const Cclass * cclsMan;
/* -------------------- /cclsMan  -------------------- */


/* --------------------  cclsBear  -------------------- */
#define cclsBear_args	int weight;\
						const char * hair
						
typedef struct cclsBear_init {
	cclsBear_args;
} cclsBear_init;

#define cclsBear_base	int weight;\
						cciString hair;\
						void (*roar)(void * self);\
						void (*printBearInfo)(void * self)
						
typedef struct cclsBear_class {
	Cclass * cclass;
	cclsBear_base;
} cclsBear_class, * cciBear;

extern const Cclass * cclsBear;
/* -------------------- /cclsBear  -------------------- */


/* --------------------  cclsPug  -------------------- */
#define cclsPug_args	void * dummy	// <-- exists for completeness

typedef struct cclsPug_init {
	cclsPug_args;
} cclsPug_init;

#define cclsPug_base	void (*snort)(void * self)
						
typedef struct cclsPug_class {
	Cclass * cclass;
	cclsPug_base;
} cclsPug_class, * cciPug;

extern const Cclass * cclsPug;
/* -------------------- /cclsPug  -------------------- */

/* --------------------  cclsManBearPug  -------------------- */
#define cclsManBearPug_args	cclsMan_args;\
							cclsBear_args;\
							cclsPug_args	// <-- don't need it; it's here for completeness
							
typedef struct cclsManBearPug_init {
	cclsManBearPug_args;
} cclsManBearPug_init;

#define cclsManBearPug_base	void (*beScary)(void * self)

typedef struct cclsManBearPug_class {
	Cclass * cclass;
	mp_type this_Man;
	cclsMan_base;
	mp_type this_Bear;
	cclsBear_base;
	mp_type this_Pug;
	cclsPug_base;
	cclsManBearPug_base;
} cclsManBearPug_class, * cciManBearPug;

extern const Cclass * cclsManBearPug;
/* -------------------- /cclsManBearPug  -------------------- */
#endif