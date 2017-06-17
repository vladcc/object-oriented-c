# object-oriented-c
Why? Because we can.

"But Vlad, why would you write in C in 2017? C is not object oriented and bla bla bla boo hoo"

If you love to write in C, you have probably heard something like the above. I'm here to tell you that
you can, indeed, write object oriented code in C with all its bells and whistles. So now you can respond with 
"Pft! I can write C to be object oriented. We C programmers are cool like that."

Joking aside, some time ago a got really curious about how to do OOP in plain C. I found some examples
on the web, but nothing simple and complete. So I decided to write my own framework. Below I'm going to show you
how to write OOP in C using nothing but the compiler and the preprocessor. To my surprise, it turned out to be
pretty simple.

First I have to mention it's based on ideas from Axel Schreiner's "Object-oriented Programming in ANSI-C", 
which he is so kind to provide for free here: https://www.cs.rit.edu/~ats/books/ooc.pdf It's a great read
for anyone interested.

Before we begin, let's look at the pros and cons:

Pros:
- C speed
- Objects
- Polymorphism
- Hierarchical inheritance
- Multiple inheritance*
- Diamond inheritance*
- Virtual base classes
- Virtual methods
- Full control over how your classes behave
- Full control over where they get allocated
- Very little work upfront

* The diamond problem is a multiple inheritance problem, but here we distinguish between both as 
multiple inheritance and diamond inheritance present different quirks. 

Cons:
- Work upfront
- Having to pass the 'this' pointer manually
- You can't have members with the same names in the derived class and the ones you inherit from
- Manual handling of function pointers
- Having to constantly look up initializer lists
- No polymorphism in multiple inheritance; only a pointer to the derived class points to a valid object
- Restricted polymorphism in diamond inheritance; only pointers to the base class and the derived class point
to valid objects
- Hackery required to do multiple and diamond inheritance

A word on encapsulation: no encapsulation is used. Every member/function pointer is public. It is left to the
programmer to follow good practice. You can encapsulate, for examples, if you wrap all private members in a 
struct and put a void * to that struct in the class. But then you will have to deal with that.

Before I get into details, if you want to jump right in the code here are the make commands:

make compile_tests	- will compile all test cases for you.
make tests 			- runs the tests back to back; compiles them first if they aren't already compiled
make clean_obj		- removes the object files
make clean_bin		- removes the executable files
make clean			- removes the object files and the executables

First you should probably get familiar with the conveniton from point 3, though.

From here on I talk about all the nerdy details. Here's a brief content:

1. General ideas
2. Mechanism
3. The convetion
4. cclass.c/cclass.h and err.c/err.h
5. Instance example
6. Virtual base classes
7. Hierarchical inheritance and polymorphism
8. Multiple inheritance
9. Diamond inheritance
10. Virtual methods
11. Allocation
12. Conclusion



1. General ideas

How do we go about creating classes in C? We use structs with variables for data members and function pointers
for methods. Duh, right. You've probably guessed that already. Also, though, we take full advantage of the fact that:

#define struct_members	int a;\
						int b;\
						void (*my_method)(void)
						
struct my_struct {
	struct_members;
};

expands to:

struct my_struct {
	int a;
	int b;
	void (*my_method)(void);
};

when the preprocessor does it's work. This gives us a way of declaring class information in one place while using it
in as many places as we want. Handy, but by itself it's not enough. Along with packing the data, we also need a way to
initialize it. For this purpose we are going to use a class descriptor in the form of:

struct class_descriptor {
	type of class;
	size;
	constructor pointer;
	destructor pointer;
};

The type is a string with the name of the class, the size is the size of the class in bytes, and the constructor and destructor
pointers will point to the class constructor and destructor functions defined in its source file. The descriptor will also be
defined in the source file and each class will have a pointer to its descriptor as it's first member. This is a must.
Now we have all the informaton we need to initialize and destroy objects from a class. But we also need a mechanism.



2. Mechanism

The general mechanism of how instance initialization is going to happen is the following:
1. Declare a pointer
2. Call a function giving it the class descriptor and the arguments needed for initialization of an object of that class
3. Let the function allocate space and call the constructor
4. Set the pointer to the address of the allocated object
5. Voila

The constructor will take the address of the object and a list of its arguments, initialize the data members and function
pointers, and perform any additional tasks such as memory allocation. Destroying the object will be done by calling a function 
which takes the object pointer and calls its destructor.

Now we have a general way of creating/destroying objects. Let's define a helpful convention and we're on our way.



3. The convetion

3.1. Naming:
- A class created with this method is called a "C class" (what can I say, I got a wild imagination)
- cclass stands for "C class"
- ccls also stands for "C class"
- cci stands for "C class instance"

From here on the words cclass and class are used interchangeably.

- A class name begins with ccls
- The name of an instance begins with cci
- The initialization arguments macro is named ccls<name of the class>_args
- The initialization arguments struct is named ccls<name of the class>_init
- The class members macro is named ccls<name of the class>_base
- The class struct is named ccls<name of the class>_class
- The class descriptor is named ccls<name of the class>_descriptor
- The pointer to the descriptor is named ccls<name of the class>
- All class methods inside the source file are named as ccls<name of class>_<name of function>
- All class method pointers use just the <name of function> part

3.2. Descriptors:
- A Cclass is a class descriptor type
- Each class struct begins with a pointer to one (Cclass *)
- Each class header declares an extern const Cclass * ccls<name of the class>

3.3. Definitions:
- All class methods are defined/declared as static except diamond constructors/destructors (more on that later)
- A class defines its descriptor as static const
- A class defines a pointer to its descriptor as const
- A cci of a class is defined as a pointer to its struct

3.4. Typedefs:
- All structs are typedef-ed to their name e.g.

typedef struct my_struct {
...
} my_struct;

An example of class named MyClass which has an int, a double, and a function pointer as members will look like this:

Header:

#define cclsMyClass_args	int n;\
							double d
							
typedef struct cclsMyClass_init {
	cclsMyClass_args;
} cclsMyClass_init;

#define cclsMyClass_base	int n;\
							double d;\
							void (*foo)(void)
							
typedef struct cclsMyClass_class {
	Cclass * descriptor;
	cclsMyClass_base;
} cclsMyClass_class, * cciMyClass;

extern const Cclass * cclsMyClass;

Source:

static void cclsMyClass_ctor(void * self, void * args);
static void cclsMyClass_dtor(void * self);
static void cclsMyClass_foo(void);

static const Cclass cclsMyClass_descriptor = {
	"cclsMyClass",
	sizeof(cclsMyClass_class),
	cclsMyClass_ctor,
	cclsMyClass_dtor
};

const Cclass * cclsMyClass = &cclsMyClass_descriptor;
... implementation code ...



4. cclass.c/cclass.h and err.c/err.h

The cclass file provides the functionality for dynamically creating/destroying objects.
You can allocate the object on the heap with ccls_new(), or on the stack with the macro ccls_stack_new().
Destroying objects is done with ccls_delete() and ccls_stack_delete() respectively. ccls_delete_null() is like 
ccls_delete() but also NULLs the pointer you pass to it, so it's preferred in the main program. ccls_stack_delete()
NULLs it's pointer as well.

The err file provides facilities for basic error checking and reporting. If an error has been detected an error
message is printed to stderr and the program exits with EXIT_FAILURE. edebug_print() prints a printf style
formated string to stderr.



5. Instance example

Considering that cclsMyClass is all set up by the rules of the convention, all you need to do to use it is:

cclsMyClass_init mycls_init = {<args here>};
cciMyClass mycls_inst = ccls_new(cclsMyClass, &mycls_init);
... code ...
ccls_delete(mycls_inst);

cclsString and string_test.c are a working example of everything up to here. However, the cclsString is missing
an initializer struct, since it's easier to just pass it a string pointer, rather than creating a struct,
putting the string pointer inside, and then pass the struct.



6. Virtual base classes

We start the more involved examples with this because it's really simple and almost all of the other examples inherit 
from a virtual base. We said that the usual class declaration looks like this:

typedef struct cclsMyClass_class {
	Cclass * descriptor;
	cclsMyClass_base;
} cclsMyClass_class, * cciMyClass;

and we use the cci to declare instances. And what's the difference between an ordinary class and a virtual
base class? That's right, you can't create an instance of a virtual base class but you can have a pointer to one.
So a virtual base class is like any other, but without the cci.

typedef struct cclsMyVirtualClass_class {
	Cclass * descriptor;
	cclsMyVirtualClass_base;
} cclsMyVirtualClass_class;

Now you can't delcare an instance with cciMyVirtualClass (the compiler won't let you), but you can declare 
a pointer to one the usual way - cclsMyVirtualClass_class *

The virtual base class in our examples is the cclsAnimal.



7. Hierarchical inheritance and polymorphism

How do we do hierarchical inheritance and polymorphism? Let's say you are making a game about petting animals. 
You have your virtual animal class and now you want a class for kitties. Since a kitty is an animal, it inherits
from cclsAnimal. The code looks like this:

#define cclsCat_base	cclsAnimal_base;\
						<cat members here>
						
typedef struct cclsCat_class {
	Cclass * cat_descriptor;
	cclsCat_base;
} cclsCat_class, * cciCat;

Then in the cat constructor and destructor you call the animal constructor and destructor using the this pointer. 
This will work, because the animal class members are contained in the upper part of the cat class. This way when you have 
an animal class pointer point to a cat instance, the animal class pointer will be pointing a valid animal class object,
but with a cat class descriptor, hence the proper constructor/destructor will be called. This is what allows for 
polymorphism and this is also the reason why you can't have members with the same names in cclsAnimal and in 
cclsCat (the compiler won't let you, anyway)

You can do this type of inheritance with as many classes as you wish. If you have a class C, which is derived from
a class B, which is derived from a class A, then C's constructor will call B's constructor, which will call A's constructor.
Turtles all the way down as much as you need. Same goes for the destructors.

simple_inheritance.c demonstrates single inheritance and polymorphism using cclsAnimal and cclsCat. hierarchy_inheritance.c 
demonstrates a hierarchy of more than two classes and also has an example of virtual methods, which we will talk about later.



8. Multiple inheritance

Ok, you made your animal petting game. Now you've got some experience and want to do something more hard core. So you
decide to make a fighting game. Maybe like Mortal Kombat, but with mythical hoax creatures instead of ninjas. This way
you can have Sasquatch fight the mighty Manbearpug, which, just as the name suggests, is part man, part bear, and part pug.

Being a smart programmer, though, you know there's no need to start from scratch, so you decide to reuse some classes
you have left from a previous project. Conveniently enough, you just happen to have a class for a man, a class for a bear,
and a class for a pug lying around. These do not inherit from cclsAnimal, though, because at the time you wrote them you
didn't know about virtual base classes (See? It is important to discuss virtual base classes first.)

This is ok, however, because the Manbearpug is as much of an animal as Sasquatch is. That is to say, it isn't. So now
you set on to creating a cclsManBearPug which inherits from cclsMan, cclsBear, and cclsPug. You follow the practice of
nesting class bases and you get:

#define cclsManBearPug_base	cclsMan_base;\
							cclsBeart_base;\
							cclsPug_base;\
							<ManBearPug members>

typedef struct cclsManBearPug_class {
	Cclass * cclass;
	cclsManBearPug_base;
} cclsManBearPug_class, * cciManBearPug;

Aaand you run into a problem. With this setup you can call the ManBearPug constructor, but how do you construct the Man, the Bear,
and the Pug inside the ManBearPug? One option is to initialize their members manually, but that, except being error prone, 
defeats the whole purpose of the OO design. When we call the ManBearPug constructor we want it to call the Man, the Bear, and the Pug 
constructors for us. But how do we do that?

We can't do it by nesting the constructors inside each other the way we did for hierarchical inheritance, because these three classes 
are not derived from one another. We can call each constructor separately, but for this we would need the individual starting addresses
for each of the classes inside the derived class. We can't have these addresses, because with this set up there are no individual 
classes inside the derived class - all members get mixed together as a bunch of variables and function pointers.

So what do we do? Do we just give up finding comfort in the thought that there are big, fancy OOP languages that don't have multiple 
inheritance, so we are no worse than them? Of course not. We are C programmers. We write what we want, and goddamit, we want multiple 
inheritance because we should be able to do it!

And, sure enough, we can achieve it with just a little bit of hacking. First we need to transform the ManBearPug class from the above
to this:

#define cclsManBearPug_base	<ManBearPug members>

typedef struct cclsManBearPug_class {
	Cclass * cclass;
	mp_type this_Man;
	cclsMan_base;
	mp_type this_Bear;
	cclsBear_base;
	mp_type this_Pug;
	cclsPug_base;
	cclsManBearPug_base;
} cclsManBearPug_class, * cciManBearPug;

What's that mp_type you ask? It stands for "multiple inheritance type" and it's defined in cclass.h like so:

typedef byte * mp_type;

And the byte type is this:

typedef unsigned char byte;

So what we have done is we have separated the bases of the classes with byte pointers. But why? Because now we can use these pointers
to trick the computer into thinking that they are pointing to valid class objects. This will allow us to call their constructors. 
Yes! Pointer magic! Looks like this:

this->this_Man = ccls_mult_offset(this->this_Man);
this->this_Bear = ccls_mult_offset(this->this_Bear);
this->this_Pug = ccls_mult_offset(this->this_Pug);

ccls_mult_offset() is a macro delcared in cclass.h and it's job is to get the proper offest inside the derived class.

Now we can pass this->this_Man to the cclsMan constructor. Similar for the bear and the pug. This way we can use the three classes
internally in cclsManBearPug. This is not without it's downsides, though, because we just lost the polymorphism. A pointer to cclsMan
won't be pointing to a valid cclsMan object if you set it to point to an instance of ManBearPug. You could argue this is fine,
because the ManBearPug is a single entity and it doesn't make sense to control the man, bear, or pug inside it separately. This
may hold true in this case, but doesn't if you were writing something else, say, something more dramatic - like a game about a
person with multiple personality disorder.

You can see all of the above in action in the multiple_inheritance.c example, which uses cclsManBearPug. The classes for the man,
the bear, the pug, and the manbearpug are inside cclsManBearPug.



9. Diamond inheritance

"Ok, great, everything up to here is fine and dandy", you say, "But what if I was writing a game about a marine biologist who
discovers a new breed of animal, which is actually a cross of two other breeds? Then we should be able to treat the newly discovered
breed as an animal like any other, correct?" 

And correct you are. Also, we can. The problem is similar to the previous one. Here's what we do: let's say your marine biologist
discovers a SharkSquid breed, which is a combination of (what else?) a shark and a squid. The shark will be inheriting from the animal
class, the squid will be inheriting from the animal class, and the sharksquid will also be inheriting from the animal class.

You can represent this like so:

#define cclsSharkSquid_base	<SharkSquid members>
						
typedef struct cclsSharkSquid_class {
	Cclass * cclass;
	cclsAnimal_base;
	dp_type this_Shark;	// diamond pointer
	cclsShark_base;
	dp_type this_Squid;	// diamond pointer
	cclsSquid_base;
	cclsSharkSquid_base;
} cclsSharkSquid_class, * cciSharkSquid;

You put the base class first, then separate the bases for all the other classes. Just like multiple inheritance, but with a base class.
Here, however, instead of mp_type we have a dp_type. What does dp_type stand for, you may ask? Well, "diamond pointer type", of course!
It's also just another name for a byte pointer. The reason for it's existance is readability. However, to take the address of an 
internal derived class now we have to take into an account the base class. So we do it like this:

this->this_Shark = ccls_diamond_offset(this->this_Shark, cclsAnimal);
this->this_Squid = ccls_diamond_offset(this->this_Squid, cclsAnimal);

ccls_diamond_offset() is again a macro delcared in cclass.h and it's job is to get the proper offest inside the derived class.

But there's one more thing. We can't just pass this->this_Shark and this->this_Squid to their respective constructors, because this way
the Shark will call it's base class constructor, and the Squid will also call it's base class constructor, as they both inherit from 
cclsAnimal. In this case though, we don't want them to have a base class instances. They also physically don't. There's no 
cclsAnimal_base above cclsShark or cclsSquid. The same goes for calling the destructors. What's the solution to this? 
Nothing fancy - we write a constructor and a destructor for cclsShark and cclsSquid which do not call the cclsAnimal 
constructor/destructor. We use the convention and name them 

cclsShark_diamond_ctor()
cclsShark_diamond_dtor()

and

cclsSquid_diamond_ctor()
cclsSquid_diamond_dtor()

We also do not delcare them as static functions, because we want to put their declarations in the cclsShark and cclsSquid header files, 
so we can use them in cclsSharkSquid. That's it. We also get a bonus - what we have done self-documents in the code.

Also, here we have some polymorphism. A shark pointer and a squid pointer won't point to valid objects if pointed to a sharksquid instance,
but a pointer to a cclsAnimal_class will.

A working example of this is diamond_inheritance.c which uses cclsShark, cclsSquid, and cclsSharkSquid.



9.1. What if you want multiple inheritance where each class has it's own instance of the base class?

Well, then you could do something like this:

#define cclsSharkSquid_base	<SharkSquid members>

typedef struct cclsSharkSquid_class {
	Cclass * cclass;
	cclsAnimal_base;
	mp_type this_Shark;
	cclsAnimal_base;
	cclsShark_base;
	mp_type this_Squid;
	cclsAnimal_base;
	cclsSquid_base;
	cclsSharkSquid_base;
} cclsSharkSquid_class, * cciSharkSquid;

Then you should be able to use the ccls_mult_offset() macro and pass this->this_Shark and this->this_Squid to their normal
constructors/destructors. You won't need diamond constructors/destructors. Polymorphism will get ugly, though. You can have an
animal pointer pointing to the derived class base class and a pointer to the derived class. But for pointer to the internal
classes you'd need getter methods. Even though this should work, I haven't done it and there's no example.



10. Virtual methods

I saved this one for last, because it's actually the easiest and we can mention it in passing. 
Overriding a method from a child class is easy - all you need to do is swap the function pointer. If you want to
use the method from the child class in the derived class, you remember it. There's an example of this in hierarchy_inheritance.c,
which uses cclsAnimal, cclsCat, and cclsSwatCat. If you are wondering, a swat cat is just like a regular cat, but it is a member
of a swat team and fights crime in a jet fighter. 

One good thing about having your classes in different files is that when you delcare your functions as static, you can use the 
same function names in more than one file. Helps with documenting what you override.



11. Allocation

Be default ccls_new() allocates your object on the heap using malloc() (emalloc(), to be precise) You can have your objects allocated
on the stack by using the ccls_stack_new() macro. If you use it though, you must use ccls_stack_delete() to destroy the same objects. 
The difference between ccls_delete() and ccls_stack_delete() is that ccls_stack_delete() doesn't call free(), since you are using 
stack memory.

ccls_stack_new() makes use of the C99 compound literals. Also note that ccls_stack_new() takes an already declared cci as an argument.
So you have:

...
cciMyClass myclass_inst = ccls_new(cclsMyClass, &myclass_init);
...

vs

...
cciMyClass myclass_inst;
ccls_stack_new(myclass_inst, cclsMyClass, &myclass_init);
...

There's an example of stack allocation in stack_allocation.c which uses cclsString_stack.c



12. Conclusion

Well, that's it. That's my take on how you can go about doing OOP in C. You also get good a exercise in pointers. 
A couple of thigs I should mention are copy constructing and variable length stack arrays. You can copy construct either 
by making an initializer by getting the members of the class you want to copy, or by having a separate method you'd call after 
creating your instance. e.g.

...
cciMyClass inst1 = ccls_new(cclsMyClass, &inst1_init);

cclsMyClass_init inst2_init = {inst1->getMemberOne(inst1), inst1->getMemberTwo(inst1)};
cciMyClass inst2 = ccls_new(cclsMyClass, &inst2_init);
...

or

...
cciMyClass inst1 = ccls_new(cclsMyClass, &inst1_init);
cciMyClass inst2 = ccls_new(cclsMyClass, NULL);

inst2->setTo(inst2, inst1);
...

In the second case you'd have to check for NULL in the constructor.

If you want your class to include a variable length array located on the stack, you'd be better off declaring the array first,
and then passing it's address to a pointer.

...
cciMyClass inst1 = ccls_new(cclsMyClass, &inst1_init);

int my_array[ARR_SIZE];

inst1->useArray(inst1, my_array, ARR_SIZE);
...

or

...
cciMyClass inst1;
ccls_stack_new(inst1, cclsMyClass, &inst1_init);

int my_array[ARR_SIZE];

inst1->useArray(inst1, my_array, ARR_SIZE);
...