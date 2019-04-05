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
      printf("my_array[%d] = %3d\t",i,my_array[i]);   /*<-- A */
      printf("ptr + %d = %3d\n",i, *(ptr + i));        /*<-- B */
    }
    return 0;
}
