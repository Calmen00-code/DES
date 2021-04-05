#include <stdio.h>
#include <string.h>

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

void decToBin( int i, int arr[], int num )
{
    while ( i >= 0 )
    {
        arr[i] = num % 2; 
        num /= 2;
        --i;
    }
}

int power( int num, int exp )
{
    int i;
    int total = 1;

    if ( exp == 0 )
        total = 1;
    else
    {
        for ( i = 0; i < exp; ++i )
            total *= num;
    }
    return total;
}

int binToDec( int bin[], int size )
{
    int i, dec, exp;
    exp = dec = 0;
    for ( i = size - 1; i >= 0; --i )
    {
        dec += bin[i] * power(2, exp);
        ++exp;
    }
    return dec;
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
    char *str = "first";
    int num = strlen(str);
    printf("%d\n", num);
    return 0;
}
