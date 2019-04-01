CHAPTER 7: More on Multi-Dimensional Arrays
-------------------------------------------

In the previous chapter we noted that given

    
        #define ROWS 5
        #define COLS 10
    
        int multi[ROWS][COLS];
    

we can access individual elements of the array **multi** using either:

    
        multi[row][col]
    

or

    
        *(*(multi + row) + col)
    

To understand more fully what is going on, let us replace

    
        *(multi + row)
    

with **X** as in:

    
        *(X + col)
    

Now, from this we see that **X** is like a pointer since the expression is de-referenced and we know that **col** is an integer. Here the arithmetic being used is of a special kind called "pointer arithmetic" is being used. That means that, since we are talking about an integer array, the address pointed to by (i.e. value of) **X + col + 1** must be greater than the address **X + col** by and amount equal to **sizeof(int)**.

Since we know the memory layout for 2 dimensional arrays, we can determine that in the expression **multi + row** as used above, **multi + row + 1** must increase by value an amount equal to that needed to "point to" the next row, which in this case would be an amount equal to **COLS \* sizeof(int)**.

That says that if the expression **\*(\*(multi + row) + col)** is to be evaluated correctly at run time, the compiler must generate code which takes into consideration the value of **COLS**, i.e. the 2nd dimension. Because of the equivalence of the two forms of expression, this is true whether we are using the pointer expression as here or the array expression **multi\[row\]\[col\]**.

Thus, to evaluate either expression, a total of 5 values must be known:

1.  The address of the first element of the array, which is returned by the expression **multi**, i.e., the name of the array.
2.  The size of the type of the elements of the array, in this case **sizeof(int)**.
3.  The 2nd dimension of the array
4.  The specific index value for the first dimension, **row** in this case.
5.  The specific index value for the second dimension, **col** in this case.

Given all of that, consider the problem of designing a function to manipulate the element values of a previously declared array. For example, one which would set all the elements of the array **multi** to the value 1.

    
    
        void set_value(int m_array[][COLS])
        {
            int row, col;
            for (row = 0; row < ROWS; row++)
            {
                for (col = 0; col < COLS; col++)
                {
                    m_array[row][col] = 1;
                }
            }
        }
    
    

And to call this function we would then use:

    
        set_value(multi);
    

Now, within the function we have used the values #defined by ROWS and COLS that set the limits on the for loops. But, these #defines are just constants as far as the compiler is concerned, i.e. there is nothing to connect them to the array size within the function. **row** and **col** are local variables, of course. The formal parameter definition permits the compiler to determine the characteristics associated with the pointer value that will be passed at run time. We really don�t need the first dimension and, as will be seen later, there are occasions where we would prefer not to define it within the parameter definition, out of habit or consistency, I have not used it here. But, the second dimension must be used as has been shown in the expression for the parameter. The reason is that we need this in the evaluation of **m\_array\[row\]\[col\]** as has been described. While the parameter defines the data type (**int** in this case) and the automatic variables for row and column are defined in the for loops, only one value can be passed using a single parameter. In this case, that is the value of **multi** as noted in the call statement, i.e. the address of the first element, often referred to as a pointer to the array. Thus, the only way we have of informing the compiler of the 2nd dimension is by explicitly including it in the parameter definition.

In fact, in general all dimensions of higher order than one are needed when dealing with multi-dimensional arrays. That is if we are talking about 3 dimensional arrays, the 2nd **and** 3rd dimension must be specified in the parameter definition.

[Chapter 8: Pointers to Arrays](ch8x.md)

[Back to Table of Contents](pointers.md)
