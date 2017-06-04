#include <stdio.h>
#include "cclass.h"
#include "err.h"
#include "cclsString.h"

#define TEST_REPS 1000000
//#define MEM_TEST

int main(void)
{
#ifdef MEM_TEST
	// check for memory leaks
	puts("Check memory");
	getchar();
	
	int i;
	for (i = 0; i < TEST_REPS; ++i)
	{
		cciString strcls = ccls_new(_cclsString, "string a");
		// strcls->print(strcls);
		strcls->setTo(strcls, "another string");
		// strcls->print(strcls);
		ccls_delete(strcls);
	}
	puts("Check memory again");
	getchar();
	return 0;
#endif
	
	// functionality test
	cciString strcls_test = ccls_new(_cclsString, "first string");
	
	strcls_test->print(strcls_test);
	strcls_test->setTo(strcls_test, "second string");
	strcls_test->print(strcls_test);
	
	printf("Class type: %s\n", ccls_type_of(strcls_test));
	printf("Class size: %u\n", ccls_size_of(strcls_test));
	printf("Is the cclass type of %s?: %s\n", 
			ccls_type_of(strcls_test),
			ccls_is_type_of(strcls_test, "ccls_string") ? "yes" : "no");
	
	ccls_delete(strcls_test);
	
	return 0;
}
