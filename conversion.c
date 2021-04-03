#include <stdio.h>
#include "conversion.h"
#include "header.h"

void binaryConversion( int i, int arr[], int num )
{
    int j = i - 7;

    while ( i > j )
    {
        arr[i] = num % 2; 
        num /= 2;
        --i;
    }
    arr[i] = 0;
}
