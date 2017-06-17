#include <stdio.h>
#include "./cclass/cclass.h"
#include "./cclass/err.h"
#include "cclsManBearPug.h"

#define print_cclst(ccins) (printf("Type: %s\n", ccls_type_of((ccins))))
#define new_line()	putchar('\n')

int main(void)
{
	cclsMan_init dave_init = {"Dave", 180};
	cciMan dave = ccls_new(cclsMan, &dave_init);
	
	print_cclst(dave);
	dave->printManInfo(dave);
	dave->walk(dave);
	
	new_line();
	cclsBear_init beary_init = {300, "very hairy"};
	cciBear beary = ccls_new(cclsBear, &beary_init);
	
	print_cclst(beary);
	beary->printBearInfo(beary);
	beary->roar(beary);
	
	new_line();
	cclsPug_init puggy_init = {NULL};	// does nothing
	cciPug puggy = ccls_new(cclsPug, &puggy_init);
	
	print_cclst(puggy);
	puggy->snort(puggy);
	
	new_line();
	edebug_print("Destroy the man, bear, and pug:\n");
	ccls_delete_null(dave);
	ccls_delete_null(beary);
	ccls_delete_null(puggy);
	
	new_line();
	edebug_print("Create a ManBearPug:\n");
	cclsManBearPug_init mbp_init = {dave_init.name, dave_init.height, 
									beary_init.weight, beary_init.hair, NULL};
	cciManBearPug mbp = ccls_new(cclsManBearPug, &mbp_init);
	
	print_cclst(mbp);
	mbp->beScary(mbp);
	
	ccls_delete_null(mbp);
	
	return 0;
}