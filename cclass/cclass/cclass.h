/* cclass.h -- an interface allowing OOP in plain C */
/* v1.1 */
#ifndef CCLASS_H
#define CCLASS_H

#include <stdbool.h>

typedef unsigned char byte;

// for multiple inheritance
typedef byte * mp_type;
#define ccls_mult_offset(mult_ptr) ((mp_type)&(mult_ptr))

// for diamond inheritance
typedef byte * dp_type;
#define ccls_diamond_offset(dmnd_ptr, ccls_base) (((dp_type)&(dmnd_ptr) + sizeof((dmnd_ptr))) - ((ccls_base)->size))

typedef struct Cclass {
	const char * type;
	size_t size;
	void (*ctor)(void * self,  const void * args);
	void (*dtor)(void * self);
} Cclass;
/*
Description:
C class descriptor.
A Cclass is used by each class to hold information common for all C classes.
This information is defined to be:
1. The type of the class as a string.
2. The size of the class in bytes.
3. A pointer to the constructor.
4. A pointer to the destructor.

Use:
0. Include cclass.h and err.h in your class source/header files.
1. Define a static const Cclass in the C class source file.
2. Define a const Cclass * ccls<name of the class> and set it to point to the definition from step 1.
3. Make the first field in your class structure a Cclass *.
4. Declare an extern const Cclass * ccls<name of the class> in the class header.
5. typedef <class structure name> * cci<class name> in the header.

Now you can create instances like so:
cci<class name> = ccls_new(ccls<name of the class>, <pointer to optional arguments>);

And destroy them like this:
ccls_delete(cci<class name>);
*/

void * ccls_new(const void * cclass, const void * args);
/*
Returns: A pointer to the initialized cclass.

Description: Takes a pointer to a Cclass structure and a void pointer that can be set
to point to optional arguments for the class construtor, or be set to NULL if there aren't any.
The function sets the first field of the class (which must be a Cclass *) to point to the class descriptor,
initializes an instance of the class by calling the class constructor, and returns a pointer to 
the initialized instance.
*/

#define ccls_stack_new(ccinst, ccls, parg)	( (ccinst) = (void *)(byte[sizeof(ccls##_class)]){0},\
											(*(const Cclass **)(ccinst) = (ccls) ),\
											(ccls)->ctor((ccinst), (parg)) )
/*
Description: Works like ccls_new(), but allocates the instance on the stack.
*/

void ccls_delete(void * ccinst);
/*
Returns: Nothing.

Description: Takes a pointer to an initialized cclass and calls the class destructor.
*/

#define ccls_stack_delete(ccinst) ((*((Cclass **)(ccinst)))->dtor((ccinst)), (ccinst) = NULL)
/*
Description: Destroys a class instance allocated on the stack and NULLs the pointer.
*/

#define ccls_delete_null(ccinst) (ccls_delete((ccinst)), (ccinst) = NULL)
/*
Description: NULLs the instance pointer after calling ccls_delete().
*/

size_t ccls_size_of(const void * ccinst);
/*
Returns: the size of the class in bytes.

Description: Takes a pointer to an initialized cclass instance and reads the size field of it's descriptor.
*/

const char * ccls_type_of(const void * ccinst);
/*
Returns: A pointer to the string describing the type of the cclass.

Description: Takes a pointer to an initialized cclass instance and reads the type field of it's descriptor.
*/

bool ccls_is_type_of(const void * ccinst, const char * str);
/*
Returns: True if the type of the cclass matches the string pointed by str. False otherwise.

Description: Compares the type of the passed cclass instance with the string pointed by str.
*/
#endif