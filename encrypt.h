#ifndef ENCRYPTION
#define ENCRYPTION

#define ENCRYPT_ROUND 16
#define KEY_BITS 56
#define PC1_ROW 7, PC1_COL 8
#define SINGLE_SHIFT 0
#define DOUBLE_SHIFT 1

void encrypt( int* );
void copyAt( int*, int*, int, int );
void generateInitialKey( int, int* );
int* pc1_process( int* );
/*
void generateKey( int, int* );
void f_func( int*, int*, int* );
void xor_encrypt( int*, int* );
*/
/*void decrypt( int* );*/

void display( int*, int );

#endif
