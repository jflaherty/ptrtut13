CHAPTER 3: Pointers and Strings
-------------------------------

The study of strings is useful to further tie in the relationship between pointers and arrays. It also makes it easy to illustrate how some of the standard C string functions can be implemented. Finally it illustrates how and when pointers can and should be passed to functions.

In C, strings are arrays of characters. This is not necessarily true in other languages. In BASIC, Pascal, Fortran and various other languages, a string has its own data type. But in C it does not. In C a string is an array of characters terminated with a binary zero character (written as **'\\0'**). To start off our discussion we will write some code which, while preferred for illustrative purposes, you would probably never write in an actual program. Consider, for example:

    
        char my_string[40];
    
        my_string[0] = 'T';
        my_string[1] = 'e';
        my_string[2] = 'd':
        my_string[3] = '\0';
    
    

While one would never build a string like this, the end result is a string in that it is an array of characters **terminated with a nul character**. By definition, in C, a string is an array of characters terminated with the nul character. Be aware that "nul" is **not** the same as "NULL". The nul refers to a zero as defined by the escape sequence **'\\0'**. That is it occupies one byte of memory. NULL, on the other hand, is the name of the macro used to initialize null pointers. NULL is #defined in a header file in your C compiler, nul may not be #defined at all.

Since writing the above code would be very time consuming, C permits two alternate ways of achieving the same thing. First, one might write:

    
        char my_string[40] = {'T', 'e', 'd', '\0',};    
    

But this also takes more typing than is convenient. So, C permits:

    
        char my_string[40] = "Ted";
    

When the double quotes are used, instead of the single quotes as was done in the previous examples, the nul character ( **'\\0**' ) is automatically appended to the end of the string.

In all of the above cases, the same thing happens. The compiler sets aside an contiguous block of memory 40 bytes long to hold characters and initialized it such that the first 4 characters are **Ted\\0**.

Now, consider the following program:

    
    ------------------program 3.1-------------------------------------
    
    /* Program 3.1 from PTRTUT10.HTM   6/13/97 */
    
    #include <stdio.h>
    
    char strA[80] = "A string to be used for demonstration purposes";
    char strB[80];
    
    int main(void)
    {
    
        char *pA;     /* a pointer to type character */
        char *pB;     /* another pointer to type character */
        puts(strA);   /* show string A */
        pA = strA;    /* point pA at string A */
        puts(pA);     /* show what pA is pointing to */
        pB = strB;    /* point pB at string B */
        putchar('\n');       /* move down one line on the screen */
        while(*pA != '\0')   /* line A (see text) */
        {
            *pB++ = *pA++;   /* line B (see text) */
        }
        *pB = '\0';          /* line C (see text) */
        puts(strB);          /* show strB on screen */
        return 0;
    }
    
    --------- end program 3.1 -------------------------------------
    
        
    

In the above we start out by defining two character arrays of 80 characters each. Since these are globally defined, they are initialized to all **'\\0**'s first. Then, **strA** has the first 42 characters initialized to the string in quotes.

Now, moving into the code, we declare two character pointers and show the string on the screen. We then "point" the pointer **pA** at **strA**. That is, by means of the assignment statement we copy the address of **strA\[0\]** into our variable **pA**. We now use **puts()** to show that which is pointed to by **pA** on the screen. Consider here that the function prototype for **puts()** is:

    
        int puts(const char *s); 
    

For the moment, ignore the **const**. The parameter passed to **puts()** is a pointer, that is the **value** of a pointer (since all parameters in C are passed by value), and the value of a pointer is the address to which it points, or, simply, an address. Thus when we write **puts(strA);** as we have seen, we are passing the address of **strA\[0\]**.

Similarly, when we write **puts(pA);** we are passing the same address, since we have set **pA = strA;**

Given that, follow the code down to the **while()** statement on line A. Line A states:

While the character pointed to by **pA** (i.e. **\*pA**) is not a nul character (i.e. the terminating **'\\0**'), do the following:

Line B states: copy the character pointed to by **pA** to the space pointed to by **pB**, then increment **pA** so it points to the next character and **pB** so it points to the next space.

When we have copied the last character, **pA** now points to the terminating nul character and the loop ends. However, we have not copied the nul character. And, by definition a string in C **must** be nul terminated. So, we add the nul character with line C.

It is very educational to run this program with your debugger while watching **strA**, **strB**, **pA** and **pB** and single stepping through the program. It is even more educational if instead of simply defining **strB\[\]** as has been done above, initialize it also with something like:

    
        strB[80] = "12345678901234567890123456789012345678901234567890"
    

where the number of digits used is greater than the length of **strA** and then repeat the single stepping procedure while watching the above variables. Give these things a try!

Getting back to the prototype for **puts()** for a moment, the "const" used as a parameter modifier informs the user that the function will not modify the string pointed to by **s**, i.e. it will treat that string as a constant.

Of course, what the above program illustrates is a simple way of copying a string. After playing with the above until you have a good understanding of what is happening, we can proceed to creating our own replacement for the standard **strcpy()** that comes with C. It might look like:

    
       char *my_strcpy(char *destination, char *source)
       {
           char *p = destination;
           while (*source != '\0')
           {
               *p++ = *source++;
           }
           *p = '\0';
           return destination;
       }   
    

In this case, I have followed the practice used in the standard routine of returning a pointer to the destination.

Again, the function is designed to accept the values of two character pointers, i.e. addresses, and thus in the previous program we could write:

    
        int main(void)
        {
            my_strcpy(strB, strA);
            puts(strB);
        }    
    

I have deviated slightly from the form used in standard C which would have the prototype:

    
        char *my_strcpy(char *destination, const char *source);  
    

Here the "const" modifier is used to assure the user that the function will not modify the contents pointed to by the source pointer. You can prove this by modifying the function above, and its prototype, to include the "const" modifier as shown. Then, within the function you can add a statement which attempts to change the contents of that which is pointed to by source, such as:

    
        *source = 'X';
    

which would normally change the first character of the string to an X. The const modifier should cause your compiler to catch this as an error. Try it and see.

Now, let's consider some of the things the above examples have shown us. First off, consider the fact that **\*ptr++** is to be interpreted as returning the value pointed to by **ptr** and then incrementing the pointer value. This has to do with the precedence of the operators. Were we to write **(\*ptr)++** we would increment, not the pointer, but that which the pointer points to! i.e. if used on the first character of the above example string the 'T' would be incremented to a 'U'. You can write some simple example code to illustrate this.

Recall again that a string is nothing more than an array of characters, with the last character being a **'\\0'**. What we have done above is deal with copying an array. It happens to be an array of characters but the technique could be applied to an array of integers, doubles, etc. In those cases, however, we would not be dealing with strings and hence the end of the array would not be marked with a special value like the nul character. We could implement a version that relied on a special value to identify the end. For example, we could copy an array of positive integers by marking the end with a negative integer. On the other hand, it is more usual that when we write a function to copy an array of items other than strings we pass the function the number of items to be copied as well as the address of the array, e.g. something like the following prototype might indicate:

    
        void int_copy(int *ptrA, int *ptrB, int nbr);
    

where **nbr** is the number of integers to be copied. You might want to play with this idea and create an array of integers and see if you can write the function **int\_copy()** and make it work.

This permits using functions to manipulate large arrays. For example, if we have an array of 5000 integers that we want to manipulate with a function, we need only pass to that function the address of the array (and any auxiliary information such as nbr above, depending on what we are doing). The array itself does **not** get passed, i.e. the whole array is not copied and put on the stack before calling the function, only its address is sent.

This is different from passing, say an integer, to a function. When we pass an integer we make a copy of the integer, i.e. get its value and put it on the stack. Within the function any manipulation of the value passed can in no way effect the original integer. But, with arrays and pointers we can pass the address of the variable and hence manipulate the values of the original variables.

[Chapter 4: More on Strings](ch4x.md)

[Back to Table of Contents](pointers.md)
