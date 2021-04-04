#include <stdlib.h>
#include "ffunc.h"
#include "file.h"
#include "encrypt.h"    /* Include for display function */

void f_func( int *right, int *finalKey, int *res )
{
    int expansion_res[48];

    expansion( right, expansion_res );     /* Expansion 32-bit to 48-bit */

}

/**
* IMPORT: Array right hand side of the feistal network
*         Result of the expansion
*
* PURPOSE: Expands the array of right hand in the feistal network
*          from 32-bit to 48-bit
*/
void expansion( int* right, int *expansion_res )
{
    int *ex_table = NULL;
    int i, exIdx;

    ex_table = calloc(sizeof(int), EX_BITS);
    readTable( "expansion.txt", ex_table, 8, 6 );
 
    exIdx = 0;
    for( i = 0; i < EX_BITS; ++i )
    {
        exIdx = ex_table[i] - 1;  /* Table is 1-based while array is 0-based */
        expansion_res[i] = right[exIdx];
    }
    free(ex_table); ex_table = NULL;
}
