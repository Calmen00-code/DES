#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"
#include "encrypt.h"
#include "file.h"
#include "permutation.h"
#include "ffunc.h"
#include "conversion.h"

void encrypt( int *cipherBit, char *keyStr )
{
    int i;
    int left[32], right[32], newRight[32], initialKey[64];
    int *roundKey = NULL;
    int res[32];

    generateInitialKey( keyStr, initialKey );   /* Generate binary key bit from keyStr */

    initialPermutation( cipherBit );            /* Encode every 64-bit in the ciphertext with IP */

    /** Divide the permuted cipherBit by halves */
    copyAt( left, cipherBit, 0, 31 );
    copyAt( right, cipherBit, 32, 63 );
    
    /* ASSERTION: 16 Rounds of encryption */
    for ( i = 0; i < ENCRYPT_ROUND; ++i )
    {
        roundKey = generateKey( i, initialKey );    /* roundKey returned is 56-bit */
        f_func( right, roundKey, res );             /* 32-bit right cipherbits */
        xor_encrypt( left, res, newRight );
        copyAt( left, right, 0, 31 );               /* Example: R0 = L1 */
        copyAt( right, newRight, 0, 31 );           /* Example: R1 = f(R0, roundKey) XOR L0 */
        free(roundKey); roundKey = NULL;
    }
    mergeArray( cipherBit, left, right, 32, 32 );

    finalPermutation( cipherBit );
}

/**
 * IMPORT: keyStr: key input by the user 
 *         key: the key in binary bits to be assigned in this function
 * 
 * PURPOSE: Generate the key from 64 bit input to 56 bit
 *          If bit of the keyStr is > 64, do chopping
 *          If bit of the keyStr is < 64, do padding
 */
void generateInitialKey( char *keyStr, int *key )
{
    int i, ii, diff, keyLen;
    int ascii;
    int *keyInt; 

    keyLen = strlen(keyStr) * 8;    /* Each character consist of 8 bit */
    keyInt = calloc(sizeof(int*), keyLen);

   /**
    * Generate the initial key using the String input by user
    */
    i = 7;  /* First 8 bits in the array is 0 to 7 */
    ii = ascii = 0;
    while ( keyStr[ii] != '\0' )
    {
        ascii = (int)(keyStr[ii]);
        binaryConversion( i, keyInt, ascii );   /* i will be decrement for 8 times */
        i += 8;                                 /* Get the next last index after 8 bits being added */
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
* IMPORT: i (Integer): Decides whether the bit is single or double rotation
*         initialKey:  Key value (64-bit) from user input will be computed 
*                      to (56-bit) using permutation (PC-1)
* 
* EXPORT: initialKey with 48-bits
* PURPOSE: Generate key for f function
*/
int* generateKey( int i, int *initialKey )
{
    int *pc1_res = NULL, *pc2_res = NULL;
    int left[28], right[28], combined[56];

    pc1_res = pc1_process( initialKey );    /* Drop bits from 64 (initialKey) to 56 (pc1_res) */

    /* Split 56 bits key to half = 28 bits (each left and right) */
    copyAt( left, pc1_res, 0, 27 );
    copyAt( right, pc1_res, 28, 55 );

    /* ONE, TWO, NINE, SIXTEEN are single shifted */
    /* Rotation is performed separately for left and right */
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

void displayTable( int *displayArr, int size, int row, int col )
{
    int i, j;
    j = 0;
    for ( i = 0; i < size; ++i )
    {
        printf("%d ", displayArr[i]);
        if ( j == col - 1 ) 
        {
            printf("\n");
            j = 0;
        }
        else
            ++j;
    }
}
