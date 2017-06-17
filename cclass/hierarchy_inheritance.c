#include <stdio.h>
#include "./cclass/cclass.h"
#include "./cclass/err.h"
#include "cclsString.h"
#include "cclsAnimal.h"
#include "cclsCat.h"
#include "cclsSwatCat.h"

#define new_line()	putchar('\n')
							   
int main(void)
{
	edebug_print("Creating a cat:\n");
	cclsCat_init kitty_init = {"land", 5, "Fuzzums Longlashes", "adorable"};
	cciCat akitten = ccls_new(cclsCat, &kitty_init);
	
	edebug_print("Printing info with printAnimalInfo() from cclsAnimal:\n");
	akitten->printAnimalInfo(akitten);
	
	new_line();
	edebug_print("Printing info with printCatInfo() from cclsCat:\n");
	edebug_print("printCatInfo() calls printAnimalInfo() from the base class\n");
	akitten->printCatInfo(akitten);
	
	ccls_delete_null(akitten);
	
	new_line();
	edebug_print("Creating a SwatCat:\n");
	
	cclsSwatCat_init razor_init = {"jet fighter", 
	kitty_init.extremities, "Rezor", "radical", "fighting crime", "T-Rone"};
	
	cciSwatCat rezor = ccls_new(cclsSwatCat, &razor_init);
	
	edebug_print("Printing cat info with printCatInfo() from cclsSwatCat:\n");
	edebug_print("cclsSwatCat overrides printCatInfo() from cclsCat with its own\n");
	rezor->printCatInfo(rezor);
	
	new_line();
	edebug_print("Using printCatInfo() through cclsCat_class pointer:\n");
	
	// we could use cciCat pcat = (cciCat)rezor but with cclsCat_class * we document our intentions
	cclsCat_class * pcat = (cclsCat_class *)rezor;
	pcat->printCatInfo(pcat);
	
	new_line();
	edebug_print("Printing animal info with printAnimalInfo() through cclsAnimal_class pointer:\n");
	cclsAnimal_class * panimal = (cclsAnimal_class *)rezor;
	
	panimal->printAnimalInfo(panimal);
	
	new_line();
	edebug_print("Calling destructor through cclsCat pointer:\n");
	edebug_print("It doesn't matter if we use a cclsAnimal_class *, cclsCat_class *,\n");
	edebug_print("or the pointer to the whole cclsSwatCat; the proper\n");
	edebug_print("destructor is always going to be called\n");
	
	ccls_delete_null(pcat);
	
	return 0;
}
