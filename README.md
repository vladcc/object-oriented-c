# object-oriented-c
Why? Because we can.

"But Vlad, why would you write in C in 2017? C is not object oriented and bla bla bla boo hoo"

If you love to write in C, you have probably heard something like the above, haven't you?
Yeah, all C heads have at some point. So now you are finally able to respond with:
"Ha! Ya think? Click on this link! See?! You are wrong! Because I know C and you don't. Ha-Ha!"

Anyway. This project offers an interface and a convetion which allow writing object oriented code in plain C.
It's based on Axel Schreiner's "Object-oriented Programming in ANSI-C", which he is so kind to provide for free
here: https://www.cs.rit.edu/~ats/books/ooc.pdf

All you need to get started is to include cclass.h and err.h in your project headers/code and compile along with 
cclass.c and err.c. You can get all the details from the provided example. Below is an overview of how it works.

1. The naming convention

To keep things ordered I've decided on the following: 

- A class built and used by this method shall be called a C class (what can I say, I got a wild imagtination)
- cclass stands for "C class"
- ccls also stands for "C class"
- cci stands for "C class instance"

Here, and in the documentation, cclass and class are used interchangeably.

2. The classes

A cclass consists of the following:
- A class descriptor. It's the same for all classes. Gets defined in each class source file.
- A pointer to the class descriptor. Also gets defined in the class source, but declared as extern in the class header.
This pointer shall be named _ccls< name of the class >, and shall be passed to ccls_new().
- The class body - a struct containing a pointer to a class descriptor as it's first member and everything else after.
- A typedef of a pointer to this struct named in the format cci< name of the class >.

3. Mechanism

To use a cclass you have to first initialize it with ccls_new(). This happens like so:

cciMyClass my_class_instance = ccls_new(_cclsMyClass, < pointer to optional arguments >);

When you are done, you have to destroy the class with ccls_delete():

ccls_delete(my_class_instance);

If something goes wrong (like if malloc() fails, or you try to do something to a NULL pointer), you'll get an error message
and exit() will be called with EXIT_FAILURE. This is done by calling equit() from err.c.
equit() takes a formatted string (just like prinf()) as an argument and prints it to stderr, prefixing it with "Err: ", so
feel free to use it if you want that functionality.

That's it. The whole wide world of OOP is now in your hands (well, the most important parts of it, at least)
