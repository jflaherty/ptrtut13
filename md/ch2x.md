CHAPTER 2: Pointer types and Arrays
-----------------------------------

Okay, let's move on. Let us consider why we need to identify the _**type**_ of variable that a pointer points to, as in:

    
         int *ptr;
    

One reason for doing this is so that later, once ptr "points to" something, if we write:

    
        *ptr = 2;
    

the compiler will know how many bytes to copy into that memory location pointed to by **ptr**. If **ptr** was declared as pointing to an integer, 4 bytes would be copied. Similarly for floats and doubles the appropriate number will be copied. But, defining the type that the pointer points to permits a number of other interesting ways a compiler can interpret code. For example, consider a block in memory consisting if ten integers in a row. That is, 40 bytes of memory are set aside to hold 10 integers.

Now, let's say we point our integer pointer **ptr** at the first of these integers. Furthermore lets say that integer is located at memory location 100 (decimal). What happens when we write:

    
        ptr + 1;
     
    

Because the compiler "knows" this is a pointer (i.e. its value is an address) and that it points to an integer (its current address, 100, is the address of an integer), it adds 4 to **ptr** instead of 1, so the pointer "points to" the **next** **integer**, at memory location 104. Similarly, were the **ptr** declared as a pointer to a short, it would add 2 to it instead of 1. The same goes for other data types such as floats, doubles, or even user defined data types such as structures. This is obviously not the same kind of "addition" that we normally think of. In C it is referred to as addition using "pointer arithmetic", a term which we will come back to later.

Similarly, since **++ptr** and **ptr++** are both equivalent to **ptr + 1** (though the point in the program when **ptr** is incremented may be different), incrementing a pointer using the unary ++ operator, either pre- or post-, increments the address it stores by the amount sizeof(type) where "type" is the type of the object pointed to. (i.e. 4 for an integer).

Since a block of 10 integers located contiguously in memory is, by definition, an array of integers, this brings up an interesting relationship between arrays and pointers.

Consider the following:

    
        int my_array[] = {1,23,17,4,-5,100}; 
    

Here we have an array containing 6 integers. We refer to each of these integers by means of a subscript to **my\_array**, i.e. using **my\_array\[0\]** through **my\_array\[5\]**. But, we could alternatively access them via a pointer as follows:

    
        int *ptr;
        ptr = &my_array[0];       /* point our pointer at the first
                                     integer in our array */ 
    

And then we could print out our array either using the array notation or by dereferencing our pointer. The following code illustrates this:

    
    -----------  Program 2.1  -----------------------------------
    
    /* Program 2.1 from PTRTUT10.HTM   6/13/97 */
    
    #include <stdio.h>
    
    int my_array[] = {1,23,17,4,-5,100};
    int *ptr;
    
    int main(void)
    {
        int i;
        ptr = &my_array[0];     /* point our pointer to the first
                                          element of the array */
        printf("\n\n");
        for (i = 0; i < 6; i++)
        {
          printf("my_array[%d] = %d   ",i,my_array[i]);   /*<-- A */
          printf("ptr + %d = %d\n",i, *(ptr + i));        /*<-- B */
        }
        return 0;
    }
    

Compile and run the above program and carefully note lines A and B and that the program prints out the same values in either case. Also observe how we dereferenced our pointer in line B, i.e. we first added i to it and then dereferenced the new pointer. Change line B to read:

    
        printf("ptr + %d = %d\n",i, *ptr++);
    

and run it again... then change it to:

    
        printf("ptr + %d = %d\n",i, *(++ptr));
    

and try once more. Each time try and predict the outcome and carefully look at the actual outcome.

In C, the standard states that wherever we might use **&var\_name\[0\]** we can replace that with **var\_name**, thus in our code where we wrote:

    
        ptr = &my_array[0];
    

we can write:

    
        ptr = my_array;
    

to achieve the same result.

This leads many texts to state that the name of an array is a pointer. I prefer to mentally think "the name of the array is the address of first element in the array". Many beginners (including myself when I was learning) have a tendency to become confused by thinking of it as a pointer. For example, while we can write

    
        ptr = my_array;
    

we cannot write

    
        my_array = ptr;
    

The reason is that while **ptr** is a variable, **my\_array** is a constant. That is, the location at which the first element of **my\_array** will be stored cannot be changed once **my\_array\[\]** has been declared.

Earlier when discussing the term "lvalue" I cited K&R-2 where it stated:

> "An **object** is a named region of storage; an **lvalue** is an expression referring to an object".

This raises an interesting problem. Since **my\_array** is a named region of storage, why is **my\_array** in the above assignment statement not an lvalue? To resolve this problem, some refer to **my\_array** as an "unmodifiable lvalue".

Modify the example program above by changing

    
        ptr = &my_array[0];
    

to

    
        ptr = my_array;
    

and run it again to verify the results are identical.

Now, let's delve a little further into the difference between the names **ptr** and **my\_array** as used above. Some writers will refer to an array's name as a _**constant**_ pointer. What do we mean by that? Well, to understand the term "constant" in this sense, let's go back to our definition of the term "variable". When we declare a variable we set aside a spot in memory to hold the value of the appropriate type. Once that is done the name of the variable can be interpreted in one of two ways. When used on the left side of the assignment operator, the compiler interprets it as the memory location to which to move that value resulting from evaluation of the right side of the assignment operator. But, when used on the right side of the assignment operator, the name of a variable is interpreted to mean the contents stored at that memory address set aside to hold the value of that variable.

With that in mind, let's now consider the simplest of constants, as in:

    
        int i, k;
        i = 2;
    

Here, while **i** is a variable and then occupies space in the data portion of memory, **2** is a constant and, as such, instead of setting aside memory in the data segment, it is imbedded directly in the code segment of memory. That is, while writing something like **k = i;** tells the compiler to create code which at run time will look at memory location **&i** to determine the value to be moved to **k**, code created by **i = 2;** simply puts the **2** in the code and there is no referencing of the data segment. That is, both **k** and **i** are objects, but **2** is not an object.

Similarly, in the above, since **my\_array** is a constant, once the compiler establishes where the array itself is to be stored, it "knows" the address of **my\_array\[0\]** and on seeing:

    
        ptr = my_array;
    

it simply uses this address as a constant in the code segment and there is no referencing of the data segment beyond that.

This might be a good place explain further the use of the **(void \*)** expression used in Program 1.1 of Chapter 1. As we have seen we can have pointers of various types. So far we have discussed pointers to integers and pointers to characters. In coming chapters we will be learning about pointers to structures and even pointer to pointers.

Also we have learned that on different systems the size of a pointer can vary. As it turns out it is also possible that the size of a pointer can vary depending on the data type of the object to which it points. Thus, as with integers where you can run into trouble attempting to assign a long integer to a variable of type short integer, you can run into trouble attempting to assign the values of pointers of various types to pointer variables of other types.

To minimize this problem, C provides for a pointer of type void. We can declare such a pointer by writing:

    
    void *vptr;
    

A void pointer is sort of a generic pointer. For example, while C will not permit the comparison of a pointer to type integer with a pointer to type character, for example, either of these can be compared to a void pointer. Of course, as with other variables, casts can be used to convert from one type of pointer to another under the proper circumstances. In Program 1.1. of Chapter 1 I cast the pointers to integers into void pointers to make them compatible with the %p conversion specification. In later chapters other casts will be made for reasons defined therein.

Well, that's a lot of technical stuff to digest and I don't expect a beginner to understand all of it on first reading. With time and experimentation you will want to come back and re-read the first 2 chapters. But for now, let's move on to the relationship between pointers, character arrays, and strings.

[Chapter 3: Pointers and Strings](ch3x.md)

[Back to Table of Contents](pointers.md)
