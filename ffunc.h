#ifndef F_FUNCTION
#define F_FUNCTION

#define EX_BITS 48

#define TOTAL_SBOX 8    /* Row of S-Box Array */
#define SBOX_BITS 6     /* Column of S-Box Array */

/* Details of the table for S-Box */
#define TABLE_ROW 4
#define TABLE_COL 16
#define TABLE_SIZE 64

void f_func( int*, int*, int* );
void expansion( int*, int* );
void xor_round( int*, int*, int* );
/*
void sbox_subs( );
void permutation_f( );
*/

#endif
