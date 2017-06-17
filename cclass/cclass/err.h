/* err.h -- common error checking */
/* v1.1 */
#ifndef ERR_H
#define ERR_H

#include <stdio.h>

#define free_null(ptr) (free((ptr)), (ptr) = NULL)
/*
Description: Calls free() and NULLs the passed pointer.
*/

void * emalloc(size_t nbytes);
/*
Returns: A void pointer to an allocated memory block of size nbytes.

Description: Calls malloc() and returns a pointer to the requested memory block
if the allocation has been successful. Calls equit() otherwise.
*/

FILE * efopen(const char * fname, const char * mode);
/*
Returns: A file pointer to the requested file.

Description: Calls fopen() with the requested file name and mode, and returns
a file pointer to the openned file if fopen() has been successful. Calls equit() otherwise.
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