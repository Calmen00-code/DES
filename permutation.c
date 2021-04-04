#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "permutation.h"
#include "file.h"
#include "encrypt.h"

void initialPermutation( int *arr )
{
    int i;
    int *table = NULL;
    int permuteIdx;
    int *arrIP = NULL;

    arrIP = calloc(sizeof(int), IN_BITS);
    permuteIdx = 0;
    table = getInitialPermutation();
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

int* getInitialPermutation()
{
    int row = ROW_IP, col = COL_IP;
    int *ip = calloc(sizeof(int), IN_BITS);

    readTable( "ip.txt", ip, row, col );
    return ip;
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
