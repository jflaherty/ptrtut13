CHAPTER 6: Some more on Strings, and Arrays of Strings
------------------------------------------------------

Well, let's go back to strings for a bit. In the following all assignments are to be understood as being global, i.e. made outside of any function, including main().

We pointed out in an earlier chapter that we could write:

    
       char my_string[40] = "Ted";
    

which would allocate space for a 40 byte array and put the string in the first 4 bytes (three for the characters in the quotes and a 4th to handle the terminating **'\\0'**).

Actually, if all we wanted to do was store the name "Ted" we could write:

    
       char my_name[] = "Ted";
    

and the compiler would count the characters, leave room for the nul character and store the total of the four characters in memory the location of which would be returned by the array name, in this case **my\_name**.

In some code, instead of the above, you might see:

    
       char *my_name = "Ted";
    

which is an alternate approach. Is there a difference between these? The answer is.. yes. Using the array notation 4 bytes of storage in the static memory block are taken up, one for each character and one for the terminating nul character. But, in the pointer notation the same 4 bytes required, **plus** N bytes to store the pointer variable **my\_name** (where N depends on the system but is usually a minimum of 2 bytes and can be 4 or more).

In the array notation, **my\_name** is short for **&myname\[0\]** which is the address of the first element of the array. Since the location of the array is fixed during run time, this is a constant (not a variable). In the pointer notation **my\_name** is a variable. As to which is the **better** method, that depends on what you are going to do within the rest of the program.

Let's now go one step further and consider what happens if each of these declarations are done within a function as opposed to globally outside the bounds of any function.

    
    void my_function_A(char *ptr)
    {
        char a[] = "ABCDE"
        .
        .
    } 
    
    
    void my_function_B(char *ptr)
    {
        char *cp = "FGHIJ"
        .
        .
    }
    

In the case of **my\_function\_A**, the content, or value(s), of the array **a\[\]** is considered to be the data. The array is said to be initialized to the values ABCDE. In the case of **my\_function\_B**, the value of the pointer **cp** is considered to be the data. The pointer has been initialized to point to the string **FGHIJ**. In both **my\_function\_A** and **my\_function\_B** the definitions are local variables and thus the string **ABCDE** is stored on the stack, as is the value of the pointer **cp**. The string **FGHIJ** can be stored anywhere. On my system it gets stored in the data segment.

By the way, array initialization of automatic variables as I have done in **my\_function\_A** was illegal in the older K&R C and only "came of age" in the newer ANSI C. A fact that may be important when one is considering portability and backwards compatibility.

As long as we are discussing the relationship/differences between pointers and arrays, let's move on to multi-dimensional arrays. Consider, for example the array:

    
        char multi[5][10];
    

Just what does this mean? Well, let's consider it in the following light.

    
        char multi[5][10];
    

Let's take the underlined part to be the "name" of an array. Then prepending the **char** and appending the **\[10\]** we have an array of 10 characters. But, the name **multi\[5\]** is itself an array indicating that there are 5 elements each being an array of 10 characters. Hence we have an array of 5 arrays of 10 characters each..

Assume we have filled this two dimensional array with data of some kind. In memory, it might look as if it had been formed by initializing 5 separate arrays using something like:

    
        multi[0] = {'0','1','2','3','4','5','6','7','8','9'}
        multi[1] = {'a','b','c','d','e','f','g','h','i','j'}
        multi[2] = {'A','B','C','D','E','F','G','H','I','J'}
        multi[3] = {'9','8','7','6','5','4','3','2','1','0'}
        multi[4] = {'J','I','H','G','F','E','D','C','B','A'}
    
    
    

At the same time, individual elements might be addressable using syntax such as:

    
        multi[0][3] = '3'
        multi[1][7] = 'h'
        multi[4][0] = 'J'
    

Since arrays are contiguous in memory, our actual memory block for the above should look like:

    
        0123456789abcdefghijABCDEFGHIJ9876543210JIHGFEDCBA
        ^
        |_____ starting at the address &multi[0][0]
    
    

Note that I did **not** write **multi\[0\] = "0123456789"**. Had I done so a terminating **'\\0'** would have been implied since whenever double quotes are used a **'\\0**' character is appended to the characters contained within those quotes. Had that been the case I would have had to set aside room for 11 characters per row instead of 10.

My goal in the above is to illustrate how memory is laid out for 2 dimensional arrays. That is, this is a 2 dimensional array of characters, NOT an array of "strings".

Now, the compiler knows how many columns are present in the array so it can interpret **multi + 1** as the address of the 'a' in the 2nd row above. That is, it adds 10, the number of columns, to get this location. If we were dealing with integers and an array with the same dimension the compiler would add **10\*sizeof(int)** which, on my machine, would be 20. Thus, the address of the **9** in the 4th row above would be **&multi\[3\]\[0\]** or **\*(multi + 3)** in pointer notation. To get to the content of the 2nd element in the 4th row we add 1 to this address and dereference the result as in

    
        *(*(multi + 3) + 1)
    

With a little thought we can see that:

    
        *(*(multi + row) + col)    and
        multi[row][col]            yield the same results.
    

The following program illustrates this using integer arrays instead of character arrays.

    
    ------------------- program 6.1 ----------------------
    
    /* Program 6.1 from PTRTUT10.HTM   6/13/97*/
    
    #include <stdio.h>
    #define ROWS 5
    #define COLS 10
    
    int multi[ROWS][COLS];
    
    int main(void)
    {
        int row, col;
        for (row = 0; row < ROWS; row++)
        {
            for (col = 0; col < COLS; col++)
            {
                multi[row][col] = row*col;
            }
        }
    
        for (row = 0; row < ROWS; row++)
        {
            for (col = 0; col < COLS; col++)
            {
                printf("\n%d  ",multi[row][col]);
                printf("%d ",*(*(multi + row) + col));
            }
        }
    
        return 0;
    }
    ----------------- end of program 6.1 ---------------------   
    

Because of the double de-referencing required in the pointer version, the name of a 2 dimensional array is often said to be equivalent to a pointer to a pointer. With a three dimensional array we would be dealing with an array of arrays of arrays and some might say its name would be equivalent to a pointer to a pointer to a pointer. However, here we have initially set aside the block of memory for the array by defining it using array notation. Hence, we are dealing with a constant, not a variable. That is we are talking about a fixed address not a variable pointer. The dereferencing function used above permits us to access any element in the array of arrays without the need of changing the value of that address (the address of **multi\[0\]\[0\]** as given by the symbol **multi**).

[Chapter 7: More on Multi-Dimensional Arrays](ch7x.md)

[Back to Table of Contents](pointers.md)
