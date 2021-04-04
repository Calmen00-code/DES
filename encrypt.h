#ifndef ENCRYPTION
#define ENCRYPTION

#define ENCRYPT_ROUND 16

/* Rotation */
#define SINGLE_ROTATION 0
#define DOUBLE_ROTATION 1

/* PC-1 */
#define PC1_ROW 7
#define PC1_COL 8
#define PC1_BITS 56

/* PC-2 */
#define PC2_ROW 6
#define PC2_COL 8
#define PC2_BITS 48

void encrypt( int* );
void copyAt( int*, int*, int, int );
void generateInitialKey( int, int* );
int* pc1_process( int* );
int* pc2_process( int* );
int* generateKey( int, int* );
void rotateleft( int, int*, int );
int* getKeyTable( char[], int, int, int );
void mergeArray( int*, int*, int*, int, int );
/*
void f_func( int*, int*, int* );
void xor_encrypt( int*, int* );
*/
/*void decrypt( int* );*/

void display( int*, int );

#endif
