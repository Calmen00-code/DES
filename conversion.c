#include <stdio.h>
#include "conversion.h"
#include "header.h"

void binaryConversion( int *i, int arr[], int num )
{
    int size, idx;
    idx = 0;
    size = IN_BITS;

    while ( *i < size && num > 0 )
    {
        idx = *i;

        arr[idx] = num % 2; 
        num /= 2;

        *i = ++idx;
    }
}
