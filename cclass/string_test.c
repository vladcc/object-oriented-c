#include <stdio.h>
#include "./cclass/cclass.h"
#include "./cclass/err.h"
#include "cclsString.h"

#define print_ccls_info(ccls) (edebug_print("Type: %s\n", ccls_type_of((ccls))),\
							   edebug_print("Size: %u\n", (unsigned int)ccls_size_of((ccls))))

#define new_line()	putchar('\n')
							   
int main(void)
{
	cciString strcls_test = ccls_new(cclsString, "Q: What did one snowman say to the other?");
	
	print_ccls_info(strcls_test);
	
	strcls_test->print(strcls_test);
	strcls_test->setTo(strcls_test, "A: It smells like carrots.");
	strcls_test->print(strcls_test);
	
	ccls_delete(strcls_test);
	return 0;
}
