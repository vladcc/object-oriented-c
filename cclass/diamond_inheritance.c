#include <stdio.h>
#include "./cclass/cclass.h"
#include "./cclass/err.h"
#include "cclsString.h"
#include "cclsAnimal.h"
#include "cclsShark.h"
#include "cclsSquid.h"
#include "cclsSharkSquid.h"

#define new_line()	putchar('\n')
							   
int main(void)
{
	edebug_print("Creating a shark:\n");
	
	cclsShark_init shark_arg = {"the sea", 4, "we're gonna need a bigger boat"};
	cciShark shark = ccls_new(cclsShark, &shark_arg);

	shark->printAnimalInfo(shark);
	ccls_delete_null(shark);
	
	new_line();
	edebug_print("Creating an squid:\n");
	
	cclsSquid_init squid_arg = {shark_arg.habitat, 8, 135};
	cciSquid squid = ccls_new(cclsSquid, &squid_arg);
	
	squid->printAnimalInfo(squid);
	ccls_delete_null(squid);
	
	new_line();
	edebug_print("duun dun.. duun dun.. dun dun dundun dundun\n");
	
	// use the initializers we already have
	cclsSharkSquid_init shoct_arg = {shark_arg.habitat, (shark_arg.extremities + squid_arg.extremities), "world domination",
										squid_arg.iq, "playing chess on multiple boards"};
	cciSharkSquid shtopus = ccls_new(cclsSharkSquid, &shoct_arg);

	shtopus->printAnimalInfo(shtopus);
	
	new_line();
	
	edebug_print("Printing animal info through cclsAnimal_class pointer:\n");
	cclsAnimal_class * monster = (cclsAnimal_class *)shtopus;
	
	monster->printAnimalInfo(monster);
	
	new_line();
	edebug_print("Destroying the shardsquid through the base class pointer:\n");
	
	ccls_delete_null(monster);
	
	return 0;
}
