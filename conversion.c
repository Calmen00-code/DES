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

void decToBin( int i, int arr[], int num )
{
    while ( i >= 0 )
    {
        arr[i] = num % 2; 
        num /= 2;
        --i;
    }
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
