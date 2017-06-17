#include <stdio.h>
#include "./cclass/cclass.h"
#include "./cclass/err.h"
#include "cclsString_stack.h"

#define print_ccls(ccins) (printf("Type: %s\nSize: %d\n", ccls_type_of((ccins)), ccls_size_of((ccins))))
#define new_line()	putchar('\n');

int main(void)
{
	cciString_stack str;
	
	ccls_stack_new(str, cclsString_stack, "I'm on the stack!");
	
	print_ccls(str);
	new_line();
	str->print(str);
	str->setTo(str, "Now I have a different string");
	str->print(str);
	new_line();
	
	ccls_stack_delete(str);
	
	return 0;
}