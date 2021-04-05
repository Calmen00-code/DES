#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"
#include "encrypt.h"
#include "file.h"
#include "permutation.h"
#include "ffunc.h"
#include "conversion.h"

void encrypt( int *arr, char *keyStr )
{
    int i;
    int left[32], right[32], newRight[32], initialKey[64];
    int *roundKey = NULL;
    int res[32];

    initialPermutation( arr );

    copyAt( left, arr, 0, 31 );
    copyAt( right, arr, 32, 63 );

    generateInitialKey( keyStr, initialKey );
    
    for ( i = 0; i < ENCRYPT_ROUND; ++i )
    {
        roundKey = generateKey( i, initialKey );
        f_func( right, roundKey, res );
        xor_encrypt( left, res, newRight );
        copyAt( left, right, 0, 31 );
        copyAt( right, newRight, 0, 31 );
    }
    mergeArray( arr, left, right, 32, 32 );

    finalPermutation( arr );
}

void generateInitialKey( char *keyStr, int *key )
{
    int i, ii, diff, keyLen;
    int ascii;
    int *keyInt; 

    keyLen = strlen(keyStr) * 8;    /* Each character consist of 8 bit */
    keyInt = calloc(sizeof(int*), keyLen);

    /* Generate the initial key using Pseudo Random Number Generator */
    i = 7;
    ii = ascii = 0;
    while ( keyStr[ii] != '\0' )
    {
        ascii = (int)(keyStr[ii]);
        binaryConversion( i, keyInt, ascii );
        i += 8;
        ++ii;
    }

    diff = 0;
    if ( keyLen > IN_BITS )         /* Do Chopping */
    {
        /* Get the correct key length (64 Bits) */
        diff = keyLen - IN_BITS;
        keyLen -= diff;

        for ( ii = 0; ii < keyLen; ++ii )
            key[ii] = keyInt[ii];
    }
    else if ( keyLen < IN_BITS )    /* Do Padding */
    {
        /* Assign all the values for key from 0 up to keyLen first */
        for ( i = 0; i < keyLen; ++i )
            key[i] = keyInt[i];

        /* Get the correct key length (64 Bits) */
        diff = IN_BITS - keyLen;
        keyLen += diff;     

        /* Do padding on the rest of the bits */
        for ( ii = i; ii < keyLen; ++ii )
            key[ii] = 1;
    }
    else    /* Initial key length = actual key length */
        copyAt( key, keyInt, 0, 63 );

    free(keyInt); keyInt = NULL;
}

/**
* IMPORT: i (Integer) decides whether the bit 
*         is single or double rotation
* EXPORT: initialKey with 48-bits
* PURPOSE: Generate key for f function
*/
int* generateKey( int i, int *initialKey )
{
    int *pc1_res = NULL, *pc2_res = NULL;
    int left[28], right[28], combined[56];

    pc1_res = pc1_process( initialKey );    /* Drop bits from 64 (initialKey) to 56 (pc1_res) */

    /* Split pc1_res into 2 sub arrays */
    copyAt( left, pc1_res, 0, 27 );
    copyAt( right, pc1_res, 28, 55 );

    /* ONE, TWO, NINE, SIXTEEN are single shifted */
    /* Split 56 bits key to half = 28 bits (each left and right */
    if ( i == 1 || i == 2 || i == 9 || i == 16 )
    {
        rotateleft( SINGLE_ROTATION, left, 28 ); 
        rotateleft( SINGLE_ROTATION, right, 28 );
    }
    else
    {
        rotateleft( DOUBLE_ROTATION, left, 28 );
        rotateleft( DOUBLE_ROTATION, right, 28 );
    }

    /* Recombined the left and right array together */
    mergeArray(combined, left, right, 28, 28);
    pc2_res = pc2_process( combined );

    free(pc1_res); pc1_res = NULL;

    return pc2_res;
}

/**
* IMPORT: opt (Integer) decides single or double rotation
*         arr* is the splitted 56-bits key array with 28 bits (each left & right)
*
* PURPOSE: Rotation on the bit of the left or right splitted from 56 bits key
*/
void rotateleft( int opt, int *arr, int size )
{
    int i;
    int temp, temp2, last;

    i = 0;
    if ( opt == SINGLE_ROTATION )
    {
        temp = arr[i];

        for ( i = 0; i < size - 1; ++i )
            arr[i] = arr[i+1];

        last = size - 1;
        arr[last] = temp;
    }
    else
    {
        temp = arr[i];
        temp2 = arr[i+1];

        for ( i = 0; i < size - 2; ++i )
            arr[i] = arr[i + 2];

        arr[size - 2] = temp;
        arr[size - 1] = temp2;
    }
}

void xor_encrypt( int *left, int *res, int *right )
{
    int i;
    for ( i = 0; i < SPLIT_BITS; ++i )
        right[i] = left[i]^res[i];
}

int* getKeyTable( char fileName[], int row, int col, int bits )
{
    int *arr = calloc(sizeof(int), bits);
    readTable( fileName, arr, row, col );
    return arr;
}
    
void copyAt( int *dest, int *src, int start, int end )
{
    int i, j;
    j = 0;
    for ( i = start; i <= end; ++i )
    {
        dest[j] = src[i];
        ++j;
    }
}

void mergeArray( int *product, int *a, int *b, int sizeA, int sizeB )
{
    int i, j;
    for ( i = 0; i < sizeA; ++i )
        product[i] = a[i];

    j = i;  /* Continue the allocation starting from the last elemen of 'a' */

    for ( i = 0; i < sizeB; ++i )
    {
        product[j] = b[i]; 
        ++j;
    }
}

void display( int *displayArr, int flag )
{
    int i, j;
    j = 7;
    for ( i = 0; i < flag; ++i )
    {
        if ( i == j )
        {
            printf("%d ", displayArr[i]);
            j += 8;
        }
        else
            printf("%d", displayArr[i]);
    }
}
