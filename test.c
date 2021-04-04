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

void binaryConversion( int i, int arr[], int num )
{
    while ( i > 0 )
    {
        arr[i] = num % 2; 
        num /= 2;
        --i;
    }
    arr[i] = 0;
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

    int a = 1, b = 1;
    int c = 0, d = 0;
    printf("%d\n", a^d);
    printf("%d\n", b^c);
*/  
    int i;
    int arr[4];
    binaryConversion( 4, arr, 8 );
    for ( i = 0; i < 4; ++i )
        printf("%d", arr[i]);
    printf("\n");
    
    return 0;
}
