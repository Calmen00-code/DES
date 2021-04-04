#include <stdio.h>
#include <stdlib.h>
#include "ffunc.h"
#include "file.h"
#include "encrypt.h"    /* Include for display function */

void f_func( int *right, int *roundKey, int *res )
{
    int expansion_res[48], xor_res[48], s_res[32];

    expansion( right, expansion_res );     /* Expansion 32-bit to 48-bit */
    xor_round( expansion_res, roundKey, xor_res );
    sbox_subs( xor_res, s_res );
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

/**
* IMPORT: Result from expansion operation, round key generated, and pointer of the result of XOR
* PURPOSE: XOR Operation between expansion result and round key
*/
void xor_round( int *expansion_res, int *roundKey, int *xor_res )
{
    int i;
    for ( i = 0; i < EX_BITS; ++i )
        xor_res[i] = expansion_res[i]^roundKey[i];
}

void sbox_subs( int *xor_res, int *s_res )
{
    int i;
    int ii, jj, kk;
    int **sbox = NULL, process_res[32];

    /** 
     * There are 8 S-Box in total, each carries 6-bits 
     * Therefore, array of 8 rows and 6 columns are required 
     */
    sbox = calloc( sizeof(int), TOTAL_SBOX );  /* Allocating row */

    for ( i = 0; i < TOTAL_SBOX; ++i )         /* Allocating column */
        sbox[i] = calloc( sizeof(int), SBOX_BITS ); 

    /* Assigning bits from xor_res into every 8 s-box array */
    kk = 0;
    for ( ii = 0; ii < TOTAL_SBOX; ++ii )       /* Iterating through every array of s-box (Row) */
    {
        for ( jj = 0; jj < SBOX_BITS; ++jj )    /* Iterating through each bit in a s-box (Column) */
        {
            sbox[ii][jj] = xor_res[kk];
            ++kk;
        }
    }
    sbox_process( sbox, process_res );
    free_2d( sbox, TOTAL_SBOX, SBOX_BITS );
}

void sbox_process( int **sbox, int *process_res )
{
    int *table = NULL, **sbox_res = NULL;
    int i;

    /* Result will be 8 S-Box with 4 bits each */
    sbox_res = calloc( sizeof(int), TOTAL_SBOX );   
    for ( i = 0; i < TOTAL_SBOX; ++i )
        sbox_res[i] = calloc( sizeof(int), RESULT_BITS );

    table = calloc( sizeof(int), TABLE_SIZE ); 
    readTable( "sbox.txt", table, TABLE_ROW, TABLE_COL );

    for ( i = 0; i < TOTAL_SBOX; ++i )
    {
        box_process( table, sbox[i], sbox_res[i] );

    free(table); table = NULL;
}

/**
* IMPORT: table for operation and box with 6 container (representing 6 bits)
* PURPOSE: Compute the s-box substitution using the table
*/
void box_process( int *table, int *box, int *box_res )
{
    int row[2], col[4];     /* row and column that represents the S-Box Table */
    int tableRow, tableCol;
    int tableValue;

    /* First and last bit represents row in the table */
    row[0] = box[0];
    row[1] = box[5];

    /* The rest of the bits in the middle represents column in the table */
    col[0] = box[1];
    col[1] = box[2];
    col[2] = box[3];
    col[3] = box[4];

    /* Compute binary to decimal to get the location of the value in table */
    tableRow = tableCol = 0;
    tableRow = binToDec( row );
    tableCol = binToDec( col );

    tableValue = 0;
    tableValue = table[tableRow][tableCol];

    /* Decimal value of tableValue will be converted to binary of box_res */
    decToBin( tableValue, box_res );
}
