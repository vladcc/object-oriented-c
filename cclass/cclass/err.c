/* err.c -- common error checking */
/* v1.1 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "err.h"

void * emalloc(size_t nbytes)
{
	/*	1. Call malloc().
		2. Return malloc's result or die. */
	void * memp = malloc(nbytes);
	
	if (NULL == memp)
		equit("Memory allocation failed");
	
	return memp;
}

FILE * efopen(const char * fname, const char * mode)
{
	/*	1. Call fopen().
		2. Return fopen's result or die. */
	FILE * fp;
	fp = fopen (fname, mode);
	if (NULL == fp)
		equit("Couldn't open file < %s >", fname);
	
	return fp;
}

void equit(const char * msg, ...)
{
	/*	1. Print an error message.
		2. Go home. */
	va_list args;
	va_start(args, msg);
	fprintf(stderr, "Err: ");
	vfprintf(stderr, msg, args);
	va_end (args);
	putchar('\n');
	
	exit(EXIT_FAILURE);
	return;
}

void edebug_print(const char * msg, ...)
{
	/* 1. Print debug info.  */
	va_list args;
	va_start(args, msg);
	vfprintf(stderr, msg, args);
	va_end (args);
	return;
}