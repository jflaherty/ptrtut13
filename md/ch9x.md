CHAPTER 9: Pointers and Dynamic Allocation of Memory
----------------------------------------------------

There are times when it is convenient to allocate memory at run time using **malloc()**, **calloc()**, or other allocation functions. Using this approach permits postponing the decision on the size of the memory block need to store an array, for example, until run time. Or it permits using a section of memory for the storage of an array of integers at one point in time, and then when that memory is no longer needed it can be freed up for other uses, such as the storage of an array of structures.

When memory is allocated, the allocating function (such as **malloc()**, **calloc()**, etc.) returns a pointer. The type of this pointer depends on whether you are using an older K&R compiler or the newer ANSI type compiler. With the older compiler the type of the returned pointer is **char**, with the ANSI compiler it is **void**.

If you are using an older compiler, and you want to allocate memory for an array of integers you will have to cast the char pointer returned to an integer pointer. For example, to allocate space for 10 integers we might write:

    
        int *iptr;
        iptr = (int *)malloc(10 * sizeof(int));
        if (iptr == NULL)
    
        { .. ERROR ROUTINE GOES HERE .. }
    

If you are using an ANSI compliant compiler, **malloc()** returns a **void** pointer and since a void pointer can be assigned to a pointer variable of any object type, the **(int \*)** cast shown above is not needed. The array dimension can be determined at run time and is not needed at compile time. That is, the **10** above could be a variable read in from a data file or keyboard, or calculated based on some need, at run time.

Because of the equivalence between array and pointer notation, once **iptr** has been assigned as above, one can use the array notation. For example, one could write:

    
        int k;
        for (k = 0; k < 10; k++)
           iptr[k] = 2;
    

to set the values of all elements to 2.

Even with a reasonably good understanding of pointers and arrays, one place the newcomer to C is likely to stumble at first is in the dynamic allocation of multi-dimensional arrays. In general, we would like to be able to access elements of such arrays using array notation, not pointer notation, wherever possible. Depending on the application we may or may not know both dimensions at compile time. This leads to a variety of ways to go about our task.

As we have seen, when dynamically allocating a one dimensional array its dimension can be determined at run time. Now, when using dynamic allocation of higher order arrays, we never need to know the first dimension at compile time. Whether we need to know the higher dimensions depends on how we go about writing the code. Here I will discuss various methods of dynamically allocating room for 2 dimensional arrays of integers.

First we will consider cases where the 2nd dimension is known at compile time.

### METHOD 1:

One way of dealing with the problem is through the use of the **typedef** keyword. To allocate a 2 dimensional array of integers recall that the following two notations result in the same object code being generated:

    
    
        multi[row][col] = 1;     *(*(multi + row) + col) = 1;
    
    

It is also true that the following two notations generate the same code:

    
    
        multi[row]            *(multi + row)
    
    

Since the one on the right must evaluate to a pointer, the array notation on the left must also evaluate to a pointer. In fact **multi\[0\]** will return a pointer to the first integer in the first row, **multi\[1\]** a pointer to the first integer of the second row, etc. Actually, **multi\[n\]** evaluates to a pointer to that array of integers that make up the n-th row of our 2 dimensional array. That is, **multi** can be thought of as an array of arrays and **multi\[n\]** as a pointer to the n-th array of this array of arrays. Here the word **pointer** is being used to represent an address value. While such usage is common in the literature, when reading such statements one must be careful to distinguish between the constant address of an array and a variable pointer which is a data object in itself.

Consider now:

    
    
    --------------- Program 9.1 --------------------------------
    
    /* Program 9.1 from PTRTUT10.HTM  6/13/97 */
    
    #include <stdio.h>
    #include <stdlib.h>
    
    #define COLS 5
    
    typedef int RowArray[COLS];
    RowArray *rptr;
    
    int main(void)
    {
        int nrows = 10;
        int row, col;
        rptr = malloc(nrows * COLS * sizeof(int));
        for (row = 0; row < nrows; row++)
        {
            for (col = 0; col < COLS; col++)
            {
                rptr[row][col] = 17;
            }
        }
    
        return 0;
    }
    ------------- End of Prog. 9.1 --------------------------------
    
    

Here I have assumed an ANSI compiler so a cast on the void pointer returned by **malloc()** is not required. If you are using an older K&R compiler you will have to cast using:

    
        rptr = (RowArray *)malloc(.... etc.
    

Using this approach, **rptr** has all the characteristics of an array name name, (except that rptr is modifiable), and array notation may be used throughout the rest of the program. That also means that if you intend to write a function to modify the array contents, you must use COLS as a part of the formal parameter in that function, just as we did when discussing the passing of two dimensional arrays to a function.

### METHOD 2:

In the METHOD 1 above, rptr turned out to be a pointer to type "one dimensional array of COLS integers". It turns out that there is syntax which can be used for this type without the need of **typedef**. If we write:

    
    
        int (*xptr)[COLS];
    
    

the variable **xptr** will have all the same characteristics as the variable **rptr** in METHOD 1 above, and we need not use the **typedef** keyword. Here **xptr** is a pointer to an array of integers and the size of that array is given by the **#defined COLS**. The parenthesis placement makes the pointer notation predominate, even though the array notation has higher precedence. i.e. had we written

    
        int *xptr[COLS];
    

we would have defined **xptr** as an array of pointers holding the number of pointers equal to that #defined by COLS. That is not the same thing at all. However, arrays of pointers have their use in the dynamic allocation of two dimensional arrays, as will be seen in the next 2 methods.

### METHOD 3:

Consider the case where we do not know the number of elements in each row at compile time, i.e. both the number of rows and number of columns must be determined at run time. One way of doing this would be to create an array of pointers to type **int** and then allocate space for each row and point these pointers at each row. Consider:

    
    
    -------------- Program 9.2 ------------------------------------
    
    /* Program 9.2 from PTRTUT10.HTM   6/13/97 */
    
    #include <stdio.h>
    #include <stdlib.h>
    
    int main(void)
    {
        int nrows = 5;     /* Both nrows and ncols could be evaluated */
        int ncols = 10;    /* or read in at run time */
        int row;
        int **rowptr;
        rowptr = malloc(nrows * sizeof(int *));
        if (rowptr == NULL)
        {
            puts("\nFailure to allocate room for row pointers.\n");
            exit(0);
        }
    
        printf("\n\n\nIndex   Pointer(hex)   Pointer(dec)   Diff.(dec)");
    
        for (row = 0; row < nrows; row++)
        {
            rowptr[row] = malloc(ncols * sizeof(int));
            if (rowptr[row] == NULL)
            {
                printf("\nFailure to allocate for row[%d]\n",row);
                exit(0);
            }
            printf("\n%d         %p         %d", row, rowptr[row], rowptr[row]);
            if (row > 0)
            printf("              %d",(int)(rowptr[row] - rowptr[row-1]));
        }
    
        return 0;
    }
    
    --------------- End 9.2 ------------------------------------
    
    

In the above code **rowptr** is a pointer to pointer to type **int**. In this case it points to the first element of an array of pointers to type **int**. Consider the number of calls to **malloc()**:

    
    
        To get the array of pointers             1     call
        To get space for the rows                5     calls
                                              -----
                         Total                   6     calls
    

If you choose to use this approach note that while you can use the array notation to access individual elements of the array, e.g. **rowptr\[row\]\[col\] = 17;**, it does not mean that the data in the "two dimensional array" is contiguous in memory.

You can, however, use the array notation just as if it were a continuous block of memory. For example, you can write:

    
        rowptr[row][col] = 176;
    

just as if rowptr were the name of a two dimensional array created at compile time. Of course **row** and **col** must be within the bounds of the array you have created, just as with an array created at compile time.

If you want to have a contiguous block of memory dedicated to the storage of the elements in the array you can do it as follows:

### METHOD 4:

In this method we allocate a block of memory to hold the whole array first. We then create an array of pointers to point to each row. Thus even though the array of pointers is being used, the actual array in memory is contiguous. The code looks like this:

    
    ----------------- Program 9.3 -----------------------------------
    
    /* Program 9.3 from PTRTUT10.HTM   6/13/97 */
    
    #include <stdio.h>
    #include <stdlib.h>
    
    int main(void)
    {
        int **rptr;
        int *aptr;
        int *testptr;
        int k;
        int nrows = 5;     /* Both nrows and ncols could be evaluated */
        int ncols = 8;    /* or read in at run time */
        int row, col;
    
        /* we now allocate the memory for the array */
    
        aptr = malloc(nrows * ncols * sizeof(int));
        if (aptr == NULL)
        {
            puts("\nFailure to allocate room for the array");
            exit(0);
        }
    
        /* next we allocate room for the pointers to the rows */
    
        rptr = malloc(nrows * sizeof(int *));
        if (rptr == NULL)
        {
            puts("\nFailure to allocate room for pointers");
            exit(0);
        }
    
        /* and now we 'point' the pointers */
    
        for (k = 0; k < nrows; k++)
        {
            rptr[k] = aptr + (k * ncols);
        }
    
        /* Now we illustrate how the row pointers are incremented */
        printf("\n\nIllustrating how row pointers are incremented");
        printf("\n\nIndex   Pointer(hex)  Diff.(dec)");
    
        for (row = 0; row < nrows; row++)
        {
            printf("\n%d         %p", row, rptr[row]);
            if (row > 0)
            printf("              %d",(rptr[row] - rptr[row-1]));
        }
        printf("\n\nAnd now we print out the array\n");
        for (row = 0; row < nrows; row++)
        {
            for (col = 0; col < ncols; col++)
            {
                rptr[row][col] = row + col;
                printf("%d ", rptr[row][col]);
            }
            putchar('\n');
        }
    
        puts("\n");
    
        /* and here we illustrate that we are, in fact, dealing with
           a 2 dimensional array in a contiguous block of memory. */
        printf("And now we demonstrate that they are contiguous in memory\n");
    
        testptr = aptr;
        for (row = 0; row < nrows; row++)
        {
            for (col = 0; col < ncols; col++)
            {
                printf("%d ", *(testptr++));
            }
            putchar('\n');
        }
    
        return 0;
    }
    
    
    
    
    ------------- End Program 9.3 -----------------
    
    

Consider again, the number of calls to malloc()

    
        To get room for the array itself      1      call
        To get room for the array of ptrs     1      call
                                            ----
                             Total            2      calls
    
    

Now, each call to **malloc()** creates additional space overhead since **malloc()** is generally implemented by the operating system forming a linked list which contains data concerning the size of the block. But, more importantly, with large arrays (several hundred rows) keeping track of what needs to be freed when the time comes can be more cumbersome. This, combined with the contiguousness of the data block that permits initialization to all zeroes using **memset()** would seem to make the second alternative the preferred one.

As a final example on multidimensional arrays we will illustrate the dynamic allocation of a three dimensional array. This example will illustrate one more thing to watch when doing this kind of allocation. For reasons cited above we will use the approach outlined in alternative two. Consider the following code:

    
    
    ------------------- Program 9.4 -------------------------------------
    
    /* Program 9.4 from PTRTUT10.HTM   6/13/97 */
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <stddef.h>
    
    int X_DIM=16;
    int Y_DIM=5;
    int Z_DIM=3;
    
    int main(void)
    {
        char *space;
        char ***Arr3D;
        int y, z;
        ptrdiff_t diff;
    
        /* first we set aside space for the array itself */
    
        space = malloc(X_DIM * Y_DIM * Z_DIM * sizeof(char));
    
        /* next we allocate space of an array of pointers, each
           to eventually point to the first element of a
           2 dimensional array of pointers to pointers */
    
        Arr3D = malloc(Z_DIM * sizeof(char **));
    
        /* and for each of these we assign a pointer to a newly
           allocated array of pointers to a row */
    
        for (z = 0; z < Z_DIM; z++)
        {
            Arr3D[z] = malloc(Y_DIM * sizeof(char *));
    
            /* and for each space in this array we put a pointer to
               the first element of each row in the array space
               originally allocated */
    
            for (y = 0; y < Y_DIM; y++)
            {
                Arr3D[z][y] = space + (z*(X_DIM * Y_DIM) + y*X_DIM);
            }
        }
    
        /* And, now we check each address in our 3D array to see if
           the indexing of the Arr3d pointer leads through in a
           continuous manner */
    
        for (z = 0; z < Z_DIM; z++)
        {
            printf("Location of array %d is %p\n", z, *Arr3D[z]);
            for ( y = 0; y < Y_DIM; y++)
            {
                printf("  Array %d and Row %d starts at %p", z, y, Arr3D[z][y]);
                diff = Arr3D[z][y] - space;
                printf("    diff = %d  ",diff);
                printf(" z = %d  y = %d\n", z, y);
            }
        }
        return 0;
    }
    
    ------------------- End of Prog. 9.4 ----------------------------
    
    

If you have followed this tutorial up to this point you should have no problem deciphering the above on the basis of the comments alone. There are a couple of points that should be made however. Let's start with the line which reads:

    
        Arr3D[z][y] = space + (z*(X_DIM * Y_DIM) + y*X_DIM);
    

Note that here **space** is a character pointer, which is the same type as **Arr3D\[z\]\[y\]**. It is important that when adding an integer, such as that obtained by evaluation of the expression **(z\*(X\_DIM \* Y\_DIM) + y\*X\_DIM)**, to a pointer, the result is a new pointer value. And when assigning pointer values to pointer variables the data types of the value and variable must match.

[Chapter 10: Pointers to Functions](ch10x.md)

[Back to Table of Contents](pointers.md)
