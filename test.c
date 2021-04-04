#include <stdio.h>

void rotateleft( int *arr, int size )
{
    int i;
    int temp, temp2;

    i = 0;
    temp = arr[i];
    temp2 = arr[i+1];

    for ( i = 0; i < size - 2; ++i )
        arr[i] = arr[i+2];

    arr[size-2] = temp;
    arr[size-1] = temp2;
}

int main()
{
/*
    int i, size;
    int A[] = { 1, 0, 0, 1, 1 };

    size = sizeof(A) / sizeof(int);
    for ( i = 0; i < size; ++i )
        printf("%d, ", A[i]);
    printf("\n");
    rotateleft( A, size );
    for ( i = 0; i < size; ++i )
        printf("%d, ", A[i]);
    printf("\n");

    int a = 3, b = 3;
    int c = 5, d = 5;
*/  
    printf("%d\n", 3^5);
    printf("%d\n", 3^5);
    return 0;
}
