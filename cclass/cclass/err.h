/* err.h -- common error checking */
/* v1.2 */
#ifndef ERR_H
#define ERR_H

#include <stdio.h>

#define efree_null(ptr) (free((ptr)), (ptr) = NULL)

/*
Description: Calls free() and NULLs the passed pointer.
*/

#define echeck(expr) ((void)((expr) || (equit("Err: %s, %s(), line %d: (%s) failed\n", __FILE__, __func__, __LINE__, #expr), 0)))
/*
Description: Basically an assert.
*/

#define echeck_v(expr, ...) ((void)((expr) || (edebug_print("Err: %s, %s(), line %d: (%s) failed\nWhy: ", __FILE__, __func__, __LINE__, #expr), equit(__VA_ARGS__), 0)))	
/*
Description: A verbose check. You can specify a reason.
*/

void * emalloc(int nbytes);
/*
Returns: A void pointer to an allocated memory block of size nbytes.

Description: Calls malloc() and returns a pointer to the requested memory block
if the allocation has been successful. Calls equit() otherwise.
*/

FILE * efopen(const char * fname, const char * mode);
/*
Returns: A file pointer to the requested file.

Description: Calls fopen() with the requested file name and mode, and returns
a file pointer to the opened file if fopen() has been successful. Calls equit() otherwise.
*/

void equit(const char * msg, ...);
/*
Returns: Nothing.

Description: Prints a printf() style formatted string to stderr and calls exit() with EXIT_FAILURE.
*/

void edebug_print(const char * msg, ...);
/*
Returns: Nothing.

Description: Prints a printf() style formatted string to stderr.
*/
#endif