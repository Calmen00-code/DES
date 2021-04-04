#ifndef F_FUNCTION
#define F_FUNCTION

#define EX_BITS 48
#define PROCESS_RESULT_BITS 32 

#define TOTAL_SBOX 8    /* Row of S-Box Array */
#define SBOX_BITS 6     /* Column of S-Box Array */
#define RESULT_BITS 4   /* Result after each S-Box computation */

/* Details of the table for S-Box */
#define TABLE_ROW 4
#define TABLE_COL 16

void f_func( int*, int*, int* );
void expansion( int*, int* );
void xor_round( int*, int*, int* );
void sbox_subs( int*, int* );
void sbox_process( int**, int *);
void box_process( int**, int*, int* );
void free_2d_int( int**, int, int );
void free_2d_char( char**, int, int );
void allocateFileName( char** );
void display2d( int**, int, int );
/*
void permutation_f( );
*/
#endif
