#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "permutation.h"
#include "file.h"

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
