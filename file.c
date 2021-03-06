#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "permutation.h"
#include "conversion.h"
#include "header.h"
#include "file.h"
#include "encrypt.h"

void readNEncrypt( char fileName[], int *cipherBit, char *key )
{
    FILE *readPtr = NULL, *writePtr = NULL;
    char ch;
    char hex[STR] = "";
    char str[STR] = "";
    int after_cipher[8];
    int i, ii, idx;

    readPtr = fopen( fileName, "r" );
    writePtr = fopen( "cipher.txt", "w" );

    if ( readPtr == NULL )
        perror("Error while reading file ");
    else if ( writePtr == NULL )
        perror("Error while writing file ");
    else
    {
        i = 7;  /* First total binary bit will be computed is 7 */
        idx = 0;

        ch = ' ';
        ch = fgetc(readPtr);

        /* ASSERTION: file reading reaches the end */
        while ( ch != EOF )
        {
            str[idx] = ch;
            binaryConversion( i, cipherBit, (int)str[idx] );

            /* Each character in ascii = 7 bits + 1 '0' bit infront = 8 bits */
            i += 8;     

            /* Send the current block for permutation and next block to come in */
            if ( i >= IN_BITS )
            {
                i = 7;  /* Reset to initial 7 since the bits is finished at 64 bits */
                encrypt( cipherBit, key );
                binToHex( cipherBit, 64, hex );
                fprintf( writePtr, "%s", hex );
                memset(hex, 0, sizeof(hex));
                memset(str, 0, sizeof(str));
                idx = 0;
            }
            else
                ++idx;
            ch = fgetc(readPtr);
        }

        /* Check if there are character in the buffer left that is not being encrypted */
        /* No encryption can be done as DES takes in 64 bits */
        if ( strcmp( str, "" ) != 0 )
        {
            for ( ii = 0; str[ii] != '\0'; ++ii )
            {
                decToBin( 7, after_cipher, (int)str[ii] );
                binToHex( after_cipher, 8, hex );
                fprintf( writePtr, "%s", hex );
                memset(hex, 0, sizeof(hex));
            }
        }
        fclose(readPtr); readPtr = NULL;
        fclose(writePtr); writePtr = NULL;
    }
}

void readNDecrypt( char fileName[], int *cipherBit, char *key )
{
    FILE *readPtr = NULL, *writePtr = NULL;
    char ch;
    char hex[STR] = "";
    int bin[64], charBin[8];
    int i, ii, jj, flag;
    int ascii;
    int *after_decrypt = NULL, char_bit[8];

    readPtr = fopen( fileName, "r" );
    writePtr = fopen( "plaintext.txt", "w" );

    if ( readPtr == NULL )
        perror("Error while reading file ");
    else if ( writePtr == NULL )
        perror("Error while writing file ");
    else
    {
        ascii = 0;
        flag = 15;  /* Every 16 hexadecimal characters is 64 bits (0 to 16 array based) = 8 ascii characters */
        /* Every 2 hexadecimal characters is 1 bit of ascii character (8 binary bits) */
        i = 0;

        ch = ' ';
        ch = fgetc(readPtr);

        /* ASSERTION: file reading reaches the end */
        while ( ch != EOF )
        {
            hex[i] = ch;
            if ( i == flag )
            {
                hexToBin( hex, bin );
                decrypt( bin, key );

                /* Iterate for 8 binary bits for 1 ascii character */
                ii = 0;
                while ( ii < 64 )
                {
                    for ( jj = 0; jj < 8; ++jj )
                    {
                        charBin[jj] = bin[ii];
                        ++ii;
                    }
                    ascii = binToDec( charBin, 8 );     
                    fprintf( writePtr, "%c", (char)(ascii) );
                }
                i = 0;
                memset(hex, 0, sizeof(hex));
            }
            else
                ++i;
            ch = fgetc(readPtr);
        }

        /* Check if there are character in the buffer left that is not being decrypted */
        if ( strcmp( hex, "" ) != 0 )
        {
            /* Each bit of hexa is equivalent to 4 bits of binary */
            after_decrypt = (int*)calloc(sizeof(int), strlen(hex) * 4);
            hexToBin( hex, after_decrypt );

            /* Iterate for after_decrypt size */
            ii = 0; 
            while( ii < strlen(hex) * 4 ) 
            {
                /* Copy every 8 bits from after_decrypt */
                jj = 0;
                while ( jj < 8 )
                {
                    char_bit[jj] = after_decrypt[ii];
                    ++ii;
                    ++jj;
                }
                ascii = binToDec( char_bit, 8 );
                fprintf( writePtr, "%c", ascii );
            }
        }
        fclose(readPtr); readPtr = NULL;
        fclose(writePtr); writePtr = NULL;
    }
    free(after_decrypt); after_decrypt = NULL;
}

void readTest( char fileName[] )
{
    FILE *readPtr = NULL;
    char readChar = ' ';
    
    readPtr = fopen(fileName, "r");
    if ( readPtr == NULL )
        perror("Error while reading file ");
    else
    {
        readChar = fgetc(readPtr); 
        while ( readChar != EOF )
        {
            printf("%c", readChar);
            readChar = fgetc(readPtr);
        }
        fclose(readPtr); readPtr = NULL;
    }
}

void readTable( char fileName[], int *table, int row, int col )
{
    FILE *readPtr = NULL;
    int i, j, idx;
    int val = 0;

    readPtr = fopen(fileName, "r");

    if ( readPtr == NULL )
        perror("Error while reading file ");
    else
    {
        idx = 0;
        for ( i = 0; i < row; ++i )
        {
            for ( j = 0; j < col; ++j ) 
            {
                fscanf(readPtr, "%d ", &val);
                table[idx] = val;
                ++idx;
            }
            fscanf(readPtr, "\n");
        }
        fclose(readPtr); readPtr = NULL;
    }
}

void read2dTable( char fileName[], int **table, int row, int col )
{
    FILE *readPtr = NULL;
    int i, j;
    int val = 0;

    readPtr = fopen(fileName, "r");

    if ( readPtr == NULL )
        perror("Error while reading file ");
    else
    {
        for ( i = 0; i < row; ++i )
        {
            for ( j = 0; j < col; ++j )
            {
                fscanf(readPtr, "%d ", &val);
                table[i][j] = val;
            }
            fscanf(readPtr, "\n");
        }
        fclose(readPtr); readPtr = NULL;
    }
}
