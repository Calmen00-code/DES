#include <stdio.h>
#include <string.h>
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

void convertHex( char binStr[], char hex[] )
{
    if ( strcmp ( binStr, "0000" ) == 0 )
        strcpy( hex, "0" );
    else if ( strcmp( binStr, "0001" ) == 0 )
        strcpy( hex, "1" );
    else if ( strcmp( binStr, "0010" ) == 0 )
        strcpy( hex, "2" );
    else if ( strcmp( binStr, "0011" ) == 0 )
        strcpy( hex, "3" );
    else if ( strcmp( binStr, "0100" ) == 0 )
        strcpy( hex, "4" );
    else if ( strcmp( binStr, "0101" ) == 0 )
        strcpy( hex, "5" );
    else if ( strcmp( binStr, "0110" ) == 0 )
        strcpy( hex, "6" );
    else if ( strcmp( binStr, "0111" ) == 0 )
        strcpy( hex, "7" );
    else if ( strcmp( binStr, "1000" ) == 0 )
        strcpy( hex, "8" );
    else if ( strcmp( binStr, "1001" ) == 0 )
        strcpy( hex, "9" );
    else if ( strcmp( binStr, "1010" ) == 0 )
        strcpy( hex, "A" );
    else if ( strcmp( binStr, "1011" ) == 0 )
        strcpy( hex, "B" );
    else if ( strcmp( binStr, "1100" ) == 0 )
        strcpy( hex, "C" );
    else if ( strcmp( binStr, "1101" ) == 0 )
        strcpy( hex, "D" );
    else if ( strcmp( binStr, "1110" ) == 0 )
        strcpy( hex, "E" );
    else if ( strcmp( binStr, "1111" ) == 0 )
        strcpy( hex, "F" );
}

void getHex( int groupBit[], char hex[] )
{
    int i;
    char binStr[100] = "";
    char bitStr[10] = "";
    int size = 4; /* Group bit will always be 4 */

    /* Get the string representation of binary bits */
    for ( i = 0; i < size; ++i )
    {
        sprintf( bitStr, "%d", groupBit[i] );     /* Convert each integer bit to string */
        strcat( binStr, bitStr );                 /* Add bitStr into binStr */
    }
    printf("binStr: %s\n", binStr);
    convertHex( binStr, hex );
}

void binToHex( int *bin, int size, char hex[] )
{
    int i, j;
    char hexVal[100] = "";
    int flag = 4;   /* Group binary bits into 4 per group */
    int groupBit[4];

    j = 0;
    for ( i = 0; i < size; ++i )
    {
        if ( j == flag - 1 )
        {
            groupBit[j] = bin[i];
            getHex( groupBit, hexVal );
            strcat( hex, hexVal );
            j = 0;
        }
        else
        {
            groupBit[j] = bin[i];
            ++j;
        }
    }
}
