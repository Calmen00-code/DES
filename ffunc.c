#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ffunc.h"
#include "file.h"
#include "encrypt.h"    /* Include for display function */
#include "conversion.h"
#include "header.h"

/**
 * IMPORT: right: Right key bits (32-bit) splitted from the cipherBit (64-bit)
 *         roundKey: 56-bit round key 
 *
 * PURPOSE: f-function operation in the feistal network
 */
void f_func( int *right, int *roundKey, int *res )
{
    int expansion_res[48], xor_res[48], s_res[32];

    expansion( right, expansion_res );              /* Expansion 32-bit to 48-bit */
    xor_round( expansion_res, roundKey, xor_res );  /* xor_res = expansion_res [XOR] roundKey */
    sbox_subs( xor_res, s_res );
    permutation_f( s_res );
    copyAt( res, s_res, 0, 31 );
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

/**
 * IMPORT   xor_res: the result after expansion_res [XOR] roundKey (48-bit)
 *          s_res: Result of S-Box Subsitution (32-bit)
 */
void sbox_subs( int *xor_res, int *s_res )
{
    int i;
    int ii, jj, kk;
    int **sbox = NULL;  /* 2D representation of xor_res */

    /** 
     * There are 8 S-Box in total, each carries 6-bits 
     * Therefore, array of 8 rows and 6 columns are required 
     */
    sbox = (int**)calloc( TOTAL_SBOX, sizeof(int*) );  /* Allocating row (TOTAL_SBOX = 8) */

    for ( i = 0; i < TOTAL_SBOX; ++i )          /* Allocating column (SBOX_BITS = 6) */
        sbox[i] = (int*)calloc( SBOX_BITS, sizeof(int) ); 

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
    sbox_process( sbox, s_res );
    free_2d_int( sbox, TOTAL_SBOX, SBOX_BITS );
}

/**
 * IMPORT   sbox: Result of 2D representation from xor_result in ffunc
 *          process_res: Result after this function was computed
 *
 * PURPOSE  Compute each 8 bit block into 4 bit
 */
void sbox_process( int **sbox, int *process_res )
{
    int **table = NULL, **sbox_res = NULL;
    int i, j, k;
    /* The file name for every single S process (eg: S1, S2 ... S8) */
    char **sboxFileName = NULL; 

    /* Result will be 8 S-Box with 4 bits each */
    /* Allocation for the array of the result and filename (Array of Strings) */
    sbox_res = (int**)calloc( sizeof(int*), TOTAL_SBOX );   
    sboxFileName = calloc( sizeof(char*), TOTAL_SBOX );
    for ( i = 0; i < TOTAL_SBOX; ++i )      /* TOTAL_SBOX = 8 */
    {
        sbox_res[i] = (int*)calloc( sizeof(int), RESULT_BITS );   /* RESULT_BITS = 4 */
        sboxFileName[i] = calloc( sizeof(char), STR ); 
    }

    /* Allocation for the S-Table */
    table = calloc( sizeof(int*), TABLE_ROW );  /* TABLE_ROW = 4 */
    for ( i = 0; i < TABLE_ROW; ++i )
        table[i] = calloc( sizeof(int), TABLE_COL );    /* TABLE_COL = 16 */
            
    allocateFileName( sboxFileName );   /* Store all the file name into this Array of Strings */

    /* Computation of converting each 6 bits to 4 bits */
    /* TOTAL_SBOX = 8 */
    /* TABLE_ROW = 4, TABLE_COL = 16 */
    for ( i = 0; i < TOTAL_SBOX; ++i )
    {
        read2dTable( sboxFileName[i], table, TABLE_ROW, TABLE_COL );    
        box_process( table, sbox[i], sbox_res[i] );
    }

    /* Combining sbox_res (4-bit) into a single array (32-bit) */
    /* TOTAL_SBOX = 8, RESULT_BITS = 4 */
    k = 0;
    for ( i = 0; i < TOTAL_SBOX; ++i )
    {
        for ( j = 0; j < RESULT_BITS; ++j )
        {
            process_res[k] = sbox_res[i][j];
            ++k;
        }
    }
    free_2d_int( table, TABLE_ROW, TABLE_COL );
    free_2d_int( sbox_res, TOTAL_SBOX, RESULT_BITS );
    free_2d_char( sboxFileName, TOTAL_SBOX, STR );
}

/**
* IMPORT: table for operation and box with 6 container (representing 6 bits)
* PURPOSE: Compute the s-box substitution using the table
*/
void box_process( int **table, int *box, int *box_res )
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
    tableRow = binToDec( row, 2 );
    tableCol = binToDec( col, 4 );

    tableValue = 0;
    tableValue = table[tableRow][tableCol];

    /* Decimal value of tableValue will be converted to binary of box_res */
    decToBin( 3, box_res, tableValue );
}

/**
* IMPORT: Array for the File Names
* PURPOSE: Allocate each file name into the array
*/
void allocateFileName( char **sboxFileName ) 
{
    strcpy(sboxFileName[0], "sbox1.txt" );
    strcpy(sboxFileName[1], "sbox2.txt" );
    strcpy(sboxFileName[2], "sbox3.txt" );
    strcpy(sboxFileName[3], "sbox4.txt" );
    strcpy(sboxFileName[4], "sbox5.txt" );
    strcpy(sboxFileName[5], "sbox6.txt" );
    strcpy(sboxFileName[6], "sbox7.txt" );
    strcpy(sboxFileName[7], "sbox8.txt" );
}

/**
* IMPORT: Integer array from the result of S-Box Substitution (32-bit)
* PURPOSE: Permutation of f function using the result from S-Box Substitution
*/
void permutation_f( int *s_res )
{
    int i;
    int table[32], *permute_res = NULL;
    int permuteIdx = 0;

    readTable( "f-permutation.txt", table, 4, 8 ); 
    permute_res = calloc( sizeof(int*), PROCESS_RESULT_BITS );
    
    for ( i = 0; i < PROCESS_RESULT_BITS; ++i )
    {
        permuteIdx = table[i] - 1;  /* Table is 1-based while array is 0-based */
        permute_res[i] = s_res[permuteIdx];
    }

    for ( i = 0; i < PROCESS_RESULT_BITS; ++i )
        s_res[i] = permute_res[i];

    free(permute_res); permute_res = NULL;
}

void free_2d_int( int **arr, int row, int col )
{
    int i;

    for ( i = 0; i < row; ++i )
    {
        free(arr[i]);
        arr[i] = NULL;
    }
    free(arr); arr = NULL;
}

void free_2d_char( char **arr, int row, int col )
{
    int i;

    for ( i = 0; i < row; ++i )
    {
        free(arr[i]);
        arr[i] = NULL;
    }
    free(arr); arr = NULL;
}

void display2d( int **displayArr, int row, int col )
{
    int i, j, k;

    k = 5;
    for ( i = 0; i < row; ++i )
    {
        for ( j = 0; j < col; ++j )
        {
            if ( j == k )
                printf("%d ", displayArr[i][j]);
            else
                printf("%d", displayArr[i][j]);
        }
        k = 5;
    }
}
