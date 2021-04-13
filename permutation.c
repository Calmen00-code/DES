#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "permutation.h"
#include "file.h"
#include "encrypt.h"

/**
 * Encode cipherBit using permutation IP 
 */
void initialPermutation( int *cipherBit )
{
    int i;
    int *table = NULL;
    int permuteIdx;
    int *arrIP = NULL;

    arrIP = calloc(sizeof(int), IN_BITS);
    permuteIdx = 0;
    table = getInitialPermutation("ip.txt");
    for( i = 0; i < IN_BITS; ++i )
    {
        permuteIdx = table[i] - 1;  /* Table is 1-64 based while array is 0-63 based */
        arrIP[i] = cipherBit[permuteIdx];
    }

    for ( i = 0; i < IN_BITS; ++i )
        cipherBit[i] = arrIP[i];

    free(arrIP); arrIP = NULL;
    free(table); table = NULL;
}

void finalPermutation( int *arr )
{
    int i;
    int *table = NULL;
    int permuteIdx;
    int *arrIP = NULL;

    arrIP = calloc(sizeof(int), IN_BITS);
    permuteIdx = 0;
    table = getInitialPermutation("ip-reverse.txt");
    for( i = 0; i < IN_BITS; ++i )
    {
        permuteIdx = table[i] - 1;  /* Table is 1-64 based while array is 0-63 based */
        arrIP[i] = arr[permuteIdx];
    }

    for ( i = 0; i < IN_BITS; ++i )
        arr[i] = arrIP[i];

    free(arrIP); arrIP = NULL;
    free(table); table = NULL;
}

int* getInitialPermutation( char fileName[] )
{
    int row = ROW_IP, col = COL_IP;
    int *ip = calloc(sizeof(int), IN_BITS);

    readTable( fileName, ip, row, col );
    return ip;
}

/**
* IMPORT: initialKey with 64 bits
* EXPORT: Result key with 56 bits 
* PURPOSE: Chops key bit from 64 to 56
*          (Drop bits: 8, 16, 24, 32, 40, 48, 56, 64)
*
*          This will return the key bit
*/
int* pc1_process( int *initialKey )
{
    int *pc1_table = NULL, *pc1_res = NULL;
    int i, pcIdx;
    
    pc1_res = calloc(sizeof(int), PC1_BITS);    /* PC1_BITS = 56 bits */
    pc1_table = getKeyTable( "pc1.txt", PC1_ROW, PC1_COL, PC1_BITS );
    /*display(pc1_table, 56);*/

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
* IMPORT: key_pc1 with 56 bits, round_key with 48 bits
* EXPORT: Result key with 48 bits is stored in round_key
* PURPOSE: Chops down 8 bits from 56 bits key from pc1_process
*/
void pc2_process( int *key_pc1, int *round_key )
{
    int *pc2_table = NULL;
    int i, pcIdx;

    pc2_table = getKeyTable( "pc2.txt", PC2_ROW, PC2_COL, PC2_BITS );

    pcIdx = 0;
    for ( i = 0; i < PC2_BITS; ++i )
    {
        pcIdx = pc2_table[i] - 1; /* Table is 1-based while array is 0-based */
        round_key[i] = key_pc1[pcIdx];
    }
    free(pc2_table); pc2_table = NULL;
}
