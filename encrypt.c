#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"
#include "encrypt.h"

void encrypt( int *arr )
{
    int i;
    int keyLen;
    int left[32], right[32], key[64];
    /* int res[32]; */

    copyAt( left, arr, 0, 31 );
    copyAt( right, arr, 32, 63 );

    keyLen = 0;
    printf("Key Length: ");
    scanf("%d", &keyLen);
    generateInitialKey( keyLen, key );
    printf("Generated Key: ");
    display( key, IN_BITS );
    printf("\n");

    for ( i = 0; i < ENCRYPT_ROUND; ++i )
    {
        copyAt( right, left, 0, 32 );
/*
        generateKey( i, key );
        f_func( right, key, res );
        xor_encrypt( left, res );
*/
    }
}

void generateInitialKey( int keyLen, int *key )
{
    int i, ii,diff;
    int *initialKey; 
    srand(time(NULL));

    initialKey = calloc(sizeof(initialKey), keyLen);

    /* Generate the initial key using Pseudo Random Number Generator */
    for ( i = 0; i < keyLen; ++i )
        initialKey[i] = rand() % 2;

    diff = 0;
    if ( keyLen > IN_BITS )         /* Do Chopping */
    {
        /* Get the correct key length (64 Bits) */
        diff = keyLen - IN_BITS;
        keyLen -= diff;

        for ( ii = 0; ii < keyLen; ++ii )
            key[ii] = initialKey[ii];
    }
    else if ( keyLen < IN_BITS )    /* Do Padding */
    {
        /* Assign all the values for key from 0 up to keyLen first */
        for ( i = 0; i < keyLen; ++i )
            key[i] = initialKey[i];

        /* Get the correct key length (64 Bits) */
        diff = IN_BITS - keyLen;
        keyLen += diff;     

        /* Do padding on the rest of the bits */
        for ( ii = i; ii < keyLen; ++ii )
            key[ii] = rand() % 2;
    }
    else    /* Initial key length = actual key length */
        copyAt( key, initialKey, 0, 63 );

    free(initialKey); initialKey = NULL;
}

/*
void generateKey( int i, int *key )
{

void f_func( int *right, int *key, int *res )
*/
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

void display( int *displayArr, int flag )
{
    int i;
    for ( i = 0; i < flag; ++i )
        printf("%d", displayArr[i]);
}
