#ifndef ENCRYPTION
#define ENCRYPTION

#define ENCRYPT_ROUND 16

/* Rotation */
#define SINGLE_ROTATION 0
#define DOUBLE_ROTATION 1

void encrypt( int* );
void copyAt( int*, int*, int, int );
void generateInitialKey( int, int* );
int* generateKey( int, int* );
void rotateleft( int, int*, int );
int* getKeyTable( char[], int, int, int );
void mergeArray( int*, int*, int*, int, int );
/*
void xor_encrypt( int*, int* );
*/
/*void decrypt( int* );*/

void display( int*, int );

#endif
