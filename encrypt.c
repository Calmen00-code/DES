#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"
#include "encrypt.h"
#include "file.h"

void encrypt( int *arr )
{
    int i;
    int keyLen;
    int left[32], right[32], initialKey[64];
    /* int *finalKey = NULL; */
    /* int res[32]; */

    copyAt( left, arr, 0, 31 );
    copyAt( right, arr, 32, 63 );

    keyLen = 0;
    printf("Key Length: ");
    scanf("%d", &keyLen);
    generateInitialKey( keyLen, initialKey );
    printf("Initial: ");
    display(initialKey, 64);
    printf("\n");

    for ( i = 0; i < ENCRYPT_ROUND; ++i )
    {
        copyAt( right, left, 0, 32 );
        /*finalKey = */generateKey( i, initialKey );
/*
        f_func( right, finalKey, res );
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

/**
* IMPORT: initialKey with 64 bits
* EXPORT: Result key with 56 bits 
* PURPOSE: Chops key bit from 64 to 56
*          (Drop bits: 8, 16, 24, 32, 40, 48, 56, 64)
*/
int* pc1_process( int *initialKey )
{
    int *pc1_table = NULL, *pc1_res = NULL;
    int i, pcIdx;
    
    pc1_res = calloc(sizeof(int), PC1_BITS);    /* PC1_BITS = 56 bits */
    pc1_table = getKeyTable( "pc1.txt", PC1_ROW, PC1_COL, PC1_BITS );

    pcIdx = 0;
    for( i = 0; i < PC1_BITS; ++i )
    {
        pcIdx = pc1_table[i] - 1;  /* Table is 1-56 based while array is 0-55 based */
        pc1_res[i] = initialKey[pcIdx];
    }
    free(pc1_table); pc1_table = NULL;

    return pc1_res;
}

/**
* IMPORT: initialKey with 56 bits
* EXPORT: Result key with 48 bits
* PURPOSE: Chops down 8 bits from 56 bits key in pc1_process
*/
int* pc2_process( int *initialKey )
{
    int *pc2_table = NULL, *pc2_res = NULL;
    int i, pcIdx;

    pc2_res = calloc(sizeof(int), PC2_BITS);
    pc2_table = getKeyTable( "pc2.txt", PC2_ROW, PC2_COL, PC2_BITS );

    pcIdx = 0;
    for ( i = 0; i < PC2_BITS; ++i )
    {
        pcIdx = pc2_table[i] - 1; /* Table is 1-based while array is 0-based */
        pc2_res[i] = initialKey[pcIdx];
    }
    free(pc2_table); pc2_table = NULL;

    return pc2_res;
}

int* getKeyTable( char fileName[], int row, int col, int bits )
{
    int *arr = calloc(sizeof(int), bits);
    readTable( fileName, arr, row, col );
    return arr;
}
    
/*
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
