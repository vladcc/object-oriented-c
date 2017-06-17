#include <stdio.h>
#include "./cclass/cclass.h"
#include "./cclass/err.h"
#include "cclsString.h"
#include "cclsAnimal.h"
#include "cclsCat.h"

#define new_line()	putchar('\n')
							   
int main(void)
{
	edebug_print("Creating a kitten:\n");
	cclsCat_init kitty_init = {"land", 5, "Sir Pawson Purrminster", "hair in your soup"};
	cciCat pawson = ccls_new(cclsCat, &kitty_init);
	
	edebug_print("Printing animal info with printAnimalInfo() from cclsAnimal:\n");
	pawson->printAnimalInfo(pawson);
	
	new_line();
	edebug_print("Printing info with printCatInfo() from cclsCat:\n");
	pawson->printCatInfo(pawson);
	
	new_line();
	edebug_print("Using the base class to copy construct another cat:\n");
	edebug_print("Only the base is copied\n");
	
	cclsCat_init copy_init = {pawson->getHabitat(pawson), pawson->getExtremities(pawson),
								"Mittens Purrminster", "double trouble"};
								
	cciCat brother_cat = ccls_new(cclsCat, &copy_init);
	
	brother_cat->printCatInfo(brother_cat);
	
	new_line();
	edebug_print("Deleting Pawson through cciCat:\n");
	ccls_delete_null(pawson);
	
	new_line();
	edebug_print("Deleting Mittens through cclsAnimal_class pointer:\n");
	cclsAnimal_class * polymorph = (cclsAnimal_class *)brother_cat;
	
	ccls_delete_null(polymorph);
	
	edebug_print("Intentional error:\n");
	ccls_size_of(polymorph);
	return 0;
}
