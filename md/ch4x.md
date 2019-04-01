CHAPTER 4: More on Strings
--------------------------

Well, we have progressed quite a way in a short time! Let's back up a little and look at what was done in Chapter 3 on copying of strings but in a different light. Consider the following function:

    
        char *my_strcpy(char dest[], char source[])
        {
            int i = 0;
            while (source[i] != '\0')
            {
                dest[i] = source[i];
                i++;
            }
            dest[i] = '\0';
            return dest;
        }
    

Recall that strings are arrays of characters. Here we have chosen to use array notation instead of pointer notation to do the actual copying. The results are the same, i.e. the string gets copied using this notation just as accurately as it did before. This raises some interesting points which we will discuss.

Since parameters are passed by value, in both the passing of a character pointer or the name of the array as above, what actually gets passed is the address of the first element of each array. Thus, the numerical value of the parameter passed is the same whether we use a character pointer or an array name as a parameter. This would tend to imply that somehow **source\[i\]** is the same as **\*(p+i)**.

In fact, this is true, i.e wherever one writes **a\[i\]** it can be replaced with **\*(a + i)** without any problems. In fact, the compiler will create the same code in either case. Thus we see that pointer arithmetic is the same thing as array indexing. Either syntax produces the same result.

This is NOT saying that pointers and arrays are the same thing, they are not. We are only saying that to identify a given element of an array we have the choice of two syntaxes, one using array indexing and the other using pointer arithmetic, which yield identical results.

Now, looking at this last expression, part of it.. **(a + i)**, is a simple addition using the **+** operator and the rules of C state that such an expression is commutative. That is **(a + i)** is identical to **(i + a)**. Thus we could write **\*(i + a)** just as easily as **\*(a + i)**.

But **\*(i + a)** could have come from **i\[a\]** ! From all of this comes the curious truth that if:

    
        char a[20];
        int i;
    

writing

    
        a[3] = 'x';
    

is the same as writing

    
        3[a] = 'x';
    

Try it! Set up an array of characters, integers or longs, etc. and assigned the 3rd or 4th element a value using the conventional approach and then print out that value to be sure you have that working. Then reverse the array notation as I have done above. A good compiler will not balk and the results will be identical. A curiosity... nothing more!

Now, looking at our function above, when we write:

    
        dest[i] = source[i];
    

due to the fact that array indexing and pointer arithmetic yield identical results, we can write this as:

    
        *(dest + i) = *(source + i);
    

But, this takes 2 additions for each value taken on by i. Additions, generally speaking, take more time than incrementations (such as those done using the **++** operator as in **i++**). This may not be true in modern optimizing compilers, but one can never be sure. Thus, the pointer version may be a bit faster than the array version.

Another way to speed up the pointer version would be to change:

    
        while (*source != '\0')
    

to simply

    
        while (*source)
    

since the value within the parenthesis will go to zero (FALSE) at the same time in either case.

At this point you might want to experiment a bit with writing some of your own programs using pointers. Manipulating strings is a good place to experiment. You might want to write your own versions of such standard functions as:

    
        strlen();
        strcat();
        strchr();
    

and any others you might have on your system.

We will come back to strings and their manipulation through pointers in a future chapter. For now, let's move on and discuss structures for a bit.

[Chapter 5: Pointers and Structures](ch5x.md)

[Back to Table of Contents](pointers.md)
