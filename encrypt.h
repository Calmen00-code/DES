#ifndef ENCRYPTION
#define ENCRYPTION

#define ENCRYPT_ROUND 16

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
