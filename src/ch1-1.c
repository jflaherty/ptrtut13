#include <stdio.h>

int j, k;
int *ptr;

int main(void)
{
    j = 1;
    k = 2;
    ptr = &k;
    printf("\n");
    printf("j has the size %lu, value %d, and is stored at %p\n", sizeof(j), j, (void *)&j);
    printf("k has the size %lu, value %d, and is stored at %p\n", sizeof(k), k, (void *)&k);
    printf("ptr has the size %lu, value %p, and is stored at %p\n", sizeof(ptr), (void *)ptr, (void *)&ptr);
    printf("The value of the integer pointed to by ptr is %d\n", *ptr);

    return 0;
}
