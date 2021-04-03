#ifndef ENCRYPTION
#define ENCRYPTION

#define ENCRYPT_ROUND 16
#define KEY_BITS 56
#define PC1_ROW 7, PC1_COL 8
#define DROP_1 7
#define DROP_2 15
#define DROP_3 23
#define DROP_4 31
#define DROP_5 39
#define DROP_6 47
#define DROP_7 55
#define DROP_8 63

void encrypt( int* );
void copyAt( int*, int*, int, int );
void generateInitialKey( int, int* );
/*
void generateKey( int, int* );
void f_func( int*, int*, int* );
void xor_encrypt( int*, int* );
*/
/*void decrypt( int* );*/

void display( int*, int );

#endif
