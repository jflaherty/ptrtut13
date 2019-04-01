CHAPTER 8: Pointers to Arrays
-----------------------------

Pointers, of course, can be "pointed at" any type of data object, including arrays. While that was evident when we discussed program 3.1, it is important to expand on how we do this when it comes to multi-dimensional arrays.

To review, in Chapter 2 we stated that given an array of integers we could point an integer pointer at that array using:

    
        int *ptr;
        ptr = &my_array[0];       /* point our pointer at the first
                                     integer in our array */
    

As we stated there, the type of the pointer variable must match the type of the first element of the array.

In addition, we can use a pointer as a formal parameter of a function which is designed to manipulate an array. e.g.

Given:

    
        int array[3] = {'1', '5', '7'};
        void a_func(int *p);
    

Some programmers might prefer to write the function prototype as:

    
       void a_func(int p[]);
    

which would tend to inform others who might use this function that the function is designed to manipulate the elements of an array. Of course, in either case, what actually gets passed is the value of a pointer to the first element of the array, independent of which notation is used in the function prototype or definition. Note that if the array notation is used, there is no need to pass the actual dimension of the array since we are not passing the whole array, only the address to the first element.

We now turn to the problem of the 2 dimensional array. As stated in the last chapter, C interprets a 2 dimensional array as an array of one dimensional arrays. That being the case, the first element of a 2 dimensional array of integers is a one dimensional array of integers. And a pointer to a two dimensional array of integers must be a pointer to that data type. One way of accomplishing this is through the use of the keyword "typedef". typedef assigns a new name to a specified data type. For example:

    
        typedef unsigned char byte;
    

causes the name **byte** to mean type **unsigned char**. Hence

    
        byte b[10];     would be an array of unsigned characters.
    

Note that in the typedef declaration, the word **byte** has replaced that which would normally be the name of our **unsigned char**. That is, the rule for using **typedef** is that the new name for the data type is the name used in the definition of the data type. Thus in:

    
        typedef int Array[10];
    

Array becomes a data type for an array of 10 integers. i.e. **Array my\_arr;** declares **my\_arr** as an array of 10 integers and **Array arr2d\[5\];** makes **arr2d** an array of 5 arrays of 10 integers each.

Also note that **Array \*p1d;** makes **p1d** a pointer to an array of 10 integers. Because **\*p1d** points to the same type as **arr2d**, assigning the address of the two dimensional array **arr2d** to **p1d**, the pointer to a one dimensional array of 10 integers is acceptable. i.e. **p1d = &arr2d\[0\];** or **p1d = arr2d;** are both correct.

Since the data type we use for our pointer is an array of 10 integers we would expect that incrementing **p1d** by 1 would change its value by **10\*sizeof(int)**, which it does. That is, **sizeof(\*p1d)** is 20. You can prove this to yourself by writing and running a simple short program.

Now, while using typedef makes things clearer for the reader and easier on the programmer, it is not really necessary. What we need is a way of declaring a pointer like **p1d** without the need of the **typedef** keyword. It turns out that this can be done and that

    
        int (*p1d)[10];
    

is the proper declaration, i.e. **p1d** here is a pointer to an array of 10 integers just as it was under the declaration using the Array type. Note that this is different from

    
        int *p1d[10];
    

which would make **p1d** the name of an array of 10 pointers to type **int**.

[Chapter 9: Pointers and Dynamic Allocation of Memory](ch9x.md)

[Back to Table of Contents](pointers.md)
