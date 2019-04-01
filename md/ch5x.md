CHAPTER 5: Pointers and Structures
----------------------------------

As you may know, we can declare the form of a block of data containing different data types by means of a structure declaration. For example, a personnel file might contain structures which look something like:

    
        struct tag {
            char lname[20];        /* last name */
            char fname[20];        /* first name */
            int age;               /* age */
            float rate;            /* e.g. 12.75 per hour */
        };
    

Let's say we have a bunch of these structures in a disk file and we want to read each one out and print out the first and last name of each one so that we can have a list of the people in our files. The remaining information will not be printed out. We will want to do this printing with a function call and pass to that function a pointer to the structure at hand. For demonstration purposes I will use only one structure for now. But realize the goal is the writing of the function, not the reading of the file which, presumably, we know how to do.

For review, recall that we can access structure members with the dot operator as in:

    
    --------------- program 5.1 ------------------
    
    /* Program 5.1 from PTRTUT10.HTM     6/13/97 */
    
    
    #include <stdio.h>
    #include <string.h>
    
    struct tag {
        char lname[20];      /* last name */
        char fname[20];      /* first name */
        int age;             /* age */
        float rate;          /* e.g. 12.75 per hour */
    };
    
    struct tag my_struct;       /* declare the structure my_struct */
    
    int main(void)
    {
        strcpy(my_struct.lname,"Jensen");
        strcpy(my_struct.fname,"Ted");
        printf("\n%s ",my_struct.fname);
        printf("%s\n",my_struct.lname);
        return 0;
    }
    
    -------------- end of program 5.1 --------------
    

Now, this particular structure is rather small compared to many used in C programs. To the above we might want to add:

    
        date_of_hire;                  (data types not shown)
        date_of_last_raise;
        last_percent_increase;
        emergency_phone;
        medical_plan;
        Social_S_Nbr;
        etc.....
    

If we have a large number of employees, what we want to do is manipulate the data in these structures by means of functions. For example we might want a function print out the name of the employee listed in any structure passed to it. However, in the original C (Kernighan & Ritchie, 1st Edition) it was not possible to pass a structure, only a pointer to a structure could be passed. In ANSI C, it is now permissible to pass the complete structure. But, since our goal here is to learn more about pointers, we won't pursue that.

Anyway, if we pass the whole structure it means that we must copy the contents of the structure from the calling function to the called function. In systems using stacks, this is done by pushing the contents of the structure on the stack. With large structures this could prove to be a problem. However, passing a pointer uses a minimum amount of stack space.

In any case, since this is a discussion of pointers, we will discuss how we go about passing a pointer to a structure and then using it within the function.

Consider the case described, i.e. we want a function that will accept as a parameter a pointer to a structure and from within that function we want to access members of the structure. For example we want to print out the name of the employee in our example structure.

Okay, so we know that our pointer is going to point to a structure declared using struct tag. We declare such a pointer with the declaration:

    
        struct tag *st_ptr;
    

and we point it to our example structure with:

    
        st_ptr = &my_struct;
    

Now, we can access a given member by de-referencing the pointer. But, how do we de-reference the pointer to a structure? Well, consider the fact that we might want to use the pointer to set the age of the employee. We would write:

    
        (*st_ptr).age = 63;
    

Look at this carefully. It says, replace that within the parenthesis with that which **st\_ptr** points to, which is the structure **my\_struct**. Thus, this breaks down to the same as **my\_struct.age**.

However, this is a fairly often used expression and the designers of C have created an alternate syntax with the same meaning which is:

    
        st_ptr->age = 63;
    

With that in mind, look at the following program:

    
    ------------ program 5.2 ---------------------
    
    /* Program 5.2 from PTRTUT10.HTM   6/13/97 */
    
    #include <stdio.h>
    #include <string.h>
    
    struct tag{                     /* the structure type */
        char lname[20];             /* last name */
        char fname[20];             /* first name */
        int age;                    /* age */
        float rate;                 /* e.g. 12.75 per hour */
    };
    
    struct tag my_struct;           /* define the structure */
    void show_name(struct tag *p);  /* function prototype */
    
    int main(void)
    {
        struct tag *st_ptr;         /* a pointer to a structure */
        st_ptr = &my_struct;        /* point the pointer to my_struct */
        strcpy(my_struct.lname,"Jensen");
        strcpy(my_struct.fname,"Ted");
        printf("\n%s ",my_struct.fname);
        printf("%s\n",my_struct.lname);
        my_struct.age = 63;
        show_name(st_ptr);          /* pass the pointer */
        return 0;
    }
    
    void show_name(struct tag *p)
    {
        printf("\n%s ", p->fname);  /* p points to a structure */
        printf("%s ", p->lname);
        printf("%d\n", p->age);
    }
    
    -------------------- end of program 5.2 ----------------
    

Again, this is a lot of information to absorb at one time. The reader should compile and run the various code snippets and using a debugger monitor things like **my\_struct** and **p** while single stepping through the main and following the code down into the function to see what is happening.  

[Chapter 6: Some more on Strings, and Arrays of Strings](ch6x.md)

[Back to Table of Contents](pointers.md)
