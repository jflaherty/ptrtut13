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
        printf("\n%d         %p         %lu", row, (void *)rowptr[row], (unsigned long)rowptr[row]);
        if (row > 0)
        printf("              %d",(int)(rowptr[row] - rowptr[row-1]));
    }
    printf("\n");

    return 0;
}
