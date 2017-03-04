Overview

The purpose of this program is to further increase C programming skills, working a lot more with pointers and using Makefiles.

Please read this entire assignment specification before starting on the first step.

Program Description

For this assignment, you will be given the structure for a simple shared library that implements the memory allocation functions malloc() and free(). Everything is present, except for the definitions of those two functions, called Mem_Alloc() and Mem_Free() in this library.

Step One: Understand the Code

Memory allocators have two distinct tasks. First, the memory allocator asks the operating system to expand the heap portion of the process's address space by calling either sbrk() or mmap(). Second, the memory allocator doles out this memory to the calling process. This involves managing a free list of memory and finding a contiguous chunk of memory that is large enough for the user's request; when the user later frees memory, it is added back to this list.

This memory allocator is usually provided as part of a standard library, and it is not part of the OS. To be clear, the memory allocator operates entirely within the virtual address space of a single process and knows nothing about which physical pages have been allocated to this process or the mapping from logical addresses to physical addresses.

Classic malloc() and free() are defined as follows:

void *malloc(size_t size): malloc() allocates size bytes and returns a pointer to the allocated memory. The memory is not cleared.
void free(void *ptr): free() frees the memory space pointed to by ptr, which must have been returned by a previous call to malloc() (or calloc() or realloc()). Otherwise, or if free(ptr) has already been called before, undefined behavior occurs. If ptr is NULL, no operation is performed.
Create a directory for this assignment. The source code files you will need are in the directory:

   /p/course/cs354-common/public/html/alloc.program/
Copy the files Makefile, mem.c and mem.h to your own directory. You will probably copy more files for Step 3, but these 3 files are sufficient for Step 2. In mem.c is fully working code for two functions: Mem_Init() and Mem_Dump(). Look at them, and understand what they do, as well as how they accomplish their task.

Mem_Init() sets up and initializes the heap space that this module manages.

Mem_Dump() is used for debugging; it prints a list of all the memory blocks (both free and allocated). It will be incredibly useful when you are trying to determine if your code works properly. As a future programming note: take notice of this function. When you are working on implementing a complex program, a function like this that produces lots of useful information about a data structure can be well worth the time you might spend implementing it.

Step Two: Write the Code

Note: Do not change the interface. Do not change anything within file mem.h. Do not change any part of functions Mem_Init() or Mem_Dump().

Write the code to implement Mem_Alloc() and Mem_Free(). Use a best fit algorithm. When freeing memory, always coalesce. Use the linked list structure as defined and described in mem.c for your data structure; it is the one described in your textbook in section 9.9.6, and it is different than the variation described in class. Here are definitions for the functions:

void *Mem_Alloc(int size): 
Mem_Alloc() is similar to the library function malloc(). Mem_Alloc takes as an input parameter the size in bytes of the memory space to be allocated, and it returns a pointer to the start of that memory space. The function returns NULL if there is not enough contiguous free space within sizeOfRegion allocated by Mem_Init to satisfy this request. For better performance, Mem_Alloc() is to return 4-byte aligned chunks of memory. For example if a user requests 1 byte of memory, the Mem_Alloc() implementation should return 4 bytes of memory, so that the next free block will also be 4-byte aligned. To debug whether you return 4-byte aligned pointers, you could print the pointer this way:
   printf("%08x", ptr) .
The last digit should be a multiple of 4 (that is, 0, 4, 8, or C). For example, b7b2c04c is okay, and b7b2c043 is not okay.
int Mem_Free(void *ptr): 
Mem_Free() frees the memory object that ptr points to. Just like with the standard free(), if ptr is NULL, then no operation is performed. The function returns 0 on success and -1 if the ptr was not allocated by Mem_Alloc(). If ptr is NULL, also return -1.
Step Three: Test the Code

You have a provided Makefile that compiles your code in mem.c and mem.h into a shared library called libmem.so. To do the compilation, the command is

   make mem
With this shared library, it is time to test if your Mem_Alloc() and Mem_Free() implementations work. This implies that you will need to write a separate program that links in your shared library, and makes calls to the functions within this shared library. We've already written a bunch of small programs that do this, to help you get started. Our programs and a second Makefile are in

   /p/course/cs354-common/public/html/alloc.program/tests/
Copy all the files within this directory into a new directory within the one containing your shared library. Name your new directory tests.

In this directory, file testlist.txt contains a list of the tests we are giving you to help you start testing your code. The tests are ordered by difficulty. Please note that these tests are not sufficient or complete for testing your code; they are meant to help you get started.

When you run make within the tests directory, it will make executables of all the C programs in this directory. The makefile specifies the base name of the library with the option -lmem and the path, so that the linker can find the library "-L.".

gcc mymain.c -lmem -L. -o myprogram -m32
The linking step needs to use your library, libmem.so. So, you need to tell the linker where to find this file. Before you run any of the created dynamically linked executables, you will need to set the environment variable, LD_LIBRARY_PATH, so that the system can find your library at run time. Assuming you always run a testing executable from (your copy of) this same tests/ directory, and the dynamically linked library (libmem.so) is one level up, that directory (to a Linux shell) is '..', so you can use the command:
setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:..
Or, if you use bash shell:
export LD_LIBRARY_PATH=.. 
If the setenv command returns an error "LD_LIBRARY_PATH: Undefined variable", do not panic. The error implies that your shell has not defined the environment variable. In this case, run:
setenv LD_LIBRARY_PATH ..
Step Four: Design a New Test

Create a new C program that tests whether simple Mem_Free() calls work. The test should determine if a single allocation, followed by a call to Mem_Free() does the right thing. After you have debugged enough to know that it works, add to this same C program to make sure that Mem_Free() does the right thing if passed a bad pointer. A bad pointer is one with the NULL value or an address of memory space not allocated by Mem_Alloc(). Name this testing program freetests.c.
