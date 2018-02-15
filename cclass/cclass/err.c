/* err.c -- common error checking */
/* v1.2 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "err.h"

static char null_ptr_arg_err[] = "NULL pointer passed as argument";

void * emalloc(int nbytes)
{
	/*	1. Call malloc().
		2. Return malloc's result or die. */
	echeck(nbytes > 0);
		
	void * memp = malloc(nbytes);
	echeck_v(memp, "Memory allocation failed");
	
	return memp;
}

FILE * efopen(const char * fname, const char * mode)
{
	/*	1. Call fopen().
		2. Return fopen's result or die. */
	echeck_v(fname, null_ptr_arg_err), echeck_v(mode, null_ptr_arg_err);
	
	FILE * fp;
	fp = fopen (fname, mode);
	echeck_v(fp, "Couldn't open file < %s >", fname);
	
	return fp;
}

void equit(const char * msg, ...)
{
	/*	1. Print an error message.
		2. Go home. */
	va_list args;
	va_start(args, msg);
	vfprintf(stderr, msg, args);
	va_end (args);
	putchar('\n');
	
	exit(EXIT_FAILURE);
	return;
}

void edebug_print(const char * msg, ...)
{
	/* 1. Print debug string.  */
	va_list args;
	va_start(args, msg);
	vfprintf(stderr, msg, args);
	va_end (args);
	return;
}