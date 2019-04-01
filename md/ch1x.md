CHAPTER 1: What is a pointer?
-----------------------------

One of those things beginners in C find difficult is the concept of pointers. The purpose of this tutorial is to provide an introduction to pointers and their use to these beginners.

I have found that often the main reason beginners have a problem with pointers is that they have a weak or minimal feeling for variables, (as they are used in C). Thus we start with a discussion of C variables in general.

A variable in a program is something with a name, the value of which can vary. The way the compiler and linker handles this is that it assigns a specific block of memory within the computer to hold the value of that variable. The size of that block depends on the range over which the variable is allowed to vary. For example, on 32 bit PC's the size of an integer variable is 4 bytes. On older 16 bit PCs integers were 2 bytes.  In C the size of a variable type such as an integer need not be the same on all types of machines.  Further more there is more than one type of integer variable in C.  We have integers, long integers and short integers which you can read up on in any basic text on C.  This document assumes the use of a 32 bit system with 4 byte integers.

If you want to know the size of the various types of integers on your system, running the following code will give you that information.

	#include <stdio.h>
	
	int main()  
	{  
		printf("size of a short is %d\\n", sizeof(short));  
		printf("size of a int is %d\\n", sizeof(int));  
		printf("size of a long is %d\\n", sizeof(long));  
	}

When we declare a variable we inform the compiler of two things, the name of the variable and the type of the variable. For example, we declare a variable of type integer with the name **k** by writing:

    
        int k; 
    

On seeing the "int" part of this statement the compiler sets aside 4 bytes of memory (on a PC) to hold the value of the integer. It also sets up a symbol table. In that table it adds the symbol **k** and the relative address in memory where those 4 bytes were set aside.

Thus, later if we write:

    
        k = 2; 
    

we expect that, at run time when this statement is executed, the value 2 will be placed in that memory location reserved for the storage of the value of **k**. In C we refer to a variable such as the integer **k** as an "object".

In a sense there are two "values" associated with the object **k**. One is the value of the integer stored there (2 in the above example) and the other the "value" of the memory location, i.e., the address of **k**. Some texts refer to these two values with the nomenclature _**rvalue**_ (right value, pronounced "are value") and _**lvalue**_ (left value, pronounced "el value") respectively.

In some languages, the lvalue is the value permitted on the left side of the assignment operator '=' (i.e. the address where the result of evaluation of the right side ends up). The rvalue is that which is on the right side of the assignment statement, the **2** above. Rvalues cannot be used on the left side of the assignment statement. Thus: **2 = k**; is illegal.

Actually, the above definition of "lvalue" is somewhat modified for C. According to K&R II (page 197): \[1\]

> "An _**object**_ is a named region of storage; an _**lvalue**_ is an expression referring to an object."

However, at this point, the definition originally cited above is sufficient. As we become more familiar with pointers we will go into more detail on this.

Okay, now consider:

    
       int j, k; 
    
        k = 2; 
        j = 7;    <-- line 1 
        k = j;    <-- line 2 
    

In the above, the compiler interprets the **j** in line 1 as the address of the variable **j** (its lvalue) and creates code to copy the value 7 to that address. In line 2, however, the **j** is interpreted as its rvalue (since it is on the right hand side of the assignment operator '='). That is, here the **j** refers to the value _**stored**_ at the memory location set aside for **j**, in this case 7. So, the 7 is copied to the address designated by the lvalue of **k**.

In all of these examples, we are using 4 byte integers so all copying of rvalues from one storage location to the other is done by copying 4 bytes. Had we been using two byte integers, we would be copying 2 bytes.

Now, let's say that we have a reason for wanting a variable designed to hold an lvalue (an address). The size required to hold such a value depends on the system. On older desk top computers with 64K of memory total, the address of any point in memory can be contained in 2 bytes. Computers with more memory would require more bytes to hold an address.  The actual size required is not too important so long as we have a way of informing the compiler that what we want to store is an address.

Such a variable is called a _**pointer variable**_ (for reasons which hopefully will become clearer a little later). In C when we define a pointer variable we do so by preceding its name with an asterisk. In C we also give our pointer a type which, in this case, refers to the type of data stored at the address we will be storing in our pointer. For example, consider the variable declaration:

    
       int *ptr;
    

**ptr** is the name of our variable (just as **k** was the name of our integer variable). The '\*' informs the compiler that we want a pointer variable, i.e. to set aside however many bytes is required to store an address in memory. The **int** says that we intend to use our pointer variable to store the address of an integer. Such a pointer is said to "point to" an integer. However, note that when we wrote **int k;** we did not give **k** a value. If this definition is made outside of any function ANSI compliant compilers will initialize it to zero. Similarly, **ptr** has no value, that is we haven't stored an address in it in the above declaration. In this case, again if the declaration is outside of any function, it is initialized to a value guaranteed in such a way that it is guaranteed to not point to any C object or function. A pointer initialized in this manner is called a "null" pointer.

The actual bit pattern used for a null pointer may or may not evaluate to zero since it depends on the specific system on which the code is developed. To make the source code compatible between various compilers on various systems, a macro is used to represent a null pointer. That macro goes under the name NULL. Thus, setting the value of a pointer using the NULL macro, as with an assignment statement such as ptr = NULL, guarantees that the pointer has become a null pointer. Similarly, just as one can test for an integer value of zero, as in **if(k == 0)**, we can test for a null pointer using **if (ptr == NULL)**.

But, back to using our new variable **ptr**. Suppose now that we want to store in **ptr** the address of our integer variable **k**. To do this we use the unary **&** operator and write:

    
        ptr = &k; 
    

What the **&** operator does is retrieve the lvalue (address) of **k**, even though **k** is on the right hand side of the assignment operator '=', and copies that to the contents of our pointer ptr. Now, ptr is said to "point to" **k**. Bear with us now, there is only one more operator we need to discuss.

The "dereferencing operator" is the asterisk and it is used as follows:

    
        *ptr = 7; 
    

will copy 7 to the address pointed to by **ptr**. Thus if **ptr** "points to" (contains the address of) **k**, the above statement will set the value of **k** to 7. That is, when we use the '\*' this way we are referring to the value of that which ptr is pointing to, not the value of the pointer itself.

Similarly, we could write:

    
     printf("%d\n",*ptr); 
    

to print to the screen the integer value stored at the address pointed to by **ptr**;.

One way to see how all this stuff fits together would be to run the following program and then review the code and the output carefully.

    
    ------------ Program 1.1 --------------------------------- 
    
    /* Program 1.1 from PTRTUT10.TXT   6/10/97 */
    
    #include <stdio.h>
    
    int j, k;
    int *ptr;
    
    int main(void)
    {
        j = 1;
        k = 2;
        ptr = &k;
        printf("\n");
        printf("j has the value %d and is stored at %p\n", j, (void *)&j);
        printf("k has the value %d and is stored at %p\n", k, (void *)&k);
        printf("ptr has the value %p and is stored at %p\n", ptr, (void *)&ptr);
        printf("The value of the integer pointed to by ptr is %d\n", *ptr);
    
        return 0;
    }
    

Note: We have yet to discuss those aspects of C which require the use of the **(void \*)** expression used here. For now, include it in your test code. We'll explain the reason behind this expression later.

* * *

To review:

*   A variable is declared by giving it a type and a name (e.g. **int k;**)
*   A pointer variable is declared by giving it a type and a name (e.g. **int \*ptr**) where the asterisk tells the compiler that the variable named **ptr** is a pointer variable and the type tells the compiler what type the pointer is to point to (integer in this case).
*   Once a variable is declared, we can get its address by preceding its name with the unary **&** operator, as in **&k**.
*   We can "dereference" a pointer, i.e. refer to the value of that which it points to, by using the unary '\*' operator as in **\*ptr**.
*   An "lvalue" of a variable is the value of its address, i.e. where it is stored in memory. The "rvalue" of a variable is the value stored in that variable (at that address).

### References for Chapter 1:

1.  "The C Programming Language" 2nd Edition  
    B. Kernighan and D. Ritchie  
    Prentice Hall  
    ISBN 0-13-110362-8  
    

[Chapter 2: Pointer Types and Arrays](ch2x.md)

[Back to Table of Contents](pointers.md)
