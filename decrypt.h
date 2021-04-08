#ifndef DECRYPTION
#define DECRYPTION

#define ENCRYPT_ROUND 16

/* Rotation */
#define SINGLE_ROTATION 0
#define DOUBLE_ROTATION 1

#define SPLIT_BITS 32 

void decrypt( int*, char* );
void copyAt( int*, int*, int, int );
void generateInitialKey( char*, int* );
int* generateKey( int, int* );
void rotateleft( int, int*, int );
int* getKeyTable( char[], int, int, int );
void mergeArray( int*, int*, int*, int, int );
void xor_encrypt( int*, int*, int* );
void display( int*, int );

#endif
