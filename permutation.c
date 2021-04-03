#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "permutation.h"
#include "file.h"

void initialPermutation( int *arr )
{
    int i;
    int *table = NULL;
    int temp, permuteIdx;

    temp = permuteIdx = 0;
    table = getInitialPermutation();
    for( i = 0; i < IN_BITS; ++i )
    {
        permuteIdx = table[i] - 1;  /* Table is 1-64 based while array is 0-63 based */

        temp = arr[permuteIdx];
        arr[permuteIdx] = arr[i];
        arr[i] = temp;
        /* printf("arr[%d] -> arr[%d]\n", i, permuteIdx); */
    }
}

int* getInitialPermutation()
{
    int row = ROW_IP, col = COL_IP;
    /*int i, j;
    int idx = 0;*/
    int *ip = calloc(sizeof(int), IN_BITS);

    readTable( "ip.txt", ip, row, col );
/*
    printf("Table: \n\n");
    for ( i = 0; i < row; ++i )
    {
        for ( j = 0; j < col; ++j )
        {
            printf("%d ", ip[idx]);
            ++idx;
        }
        printf("\n");
    }
*/
    return ip;
}
