#include <stdio.h>
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
    int i;
    int ascii;

    readPtr = fopen( fileName, "r" );
    writePtr = fopen( "cipher.txt", "w" );

    if ( readPtr == NULL )
        perror("Error while reading file ");
    else if ( writePtr == NULL )
        perror("Error while writing file ");
    else
    {
        ascii = 0;
        i = 7;  /* First total binary bit will be computed is 7 */

        ch = ' ';
        ch = fgetc(readPtr);

        /* ASSERTION: file reading reaches the end */
        while ( ch != EOF )
        {
            /* ascii is to be converted to binary for encryption */
            ascii = (int)(ch);
            binaryConversion( i, cipherBit, ascii );

            /* Each character in ascii = 7 bits + 1 '0' bit infront = 8 bits */
            i += 8;     

            /* Send the current block for permutation and next block to come in */
            if ( i >= IN_BITS )
            {
                i = 7;  /* Reset to initial 7 since the bits is finished at 64 bits */
                encrypt( cipherBit, key );
                binToHex( cipherBit, 64, hex );
                printf("Encrypt Result: ");
                display( cipherBit, 64 );
                fprintf( writePtr, "%s", hex );
                strcpy(hex, "");
            }
            ch = fgetc(readPtr);
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
                printf("hex: %s\n", hex);
                decrypt( bin, key );
                printf("Decrypt Result: ");
                display(bin, 64);

                /* Iterate for 8 binary bits for 1 ascii character */
                ii = 0;
                while ( ii < 64 )
                {
                    for ( jj = 0; jj < 8; ++jj )
                    {
                        charBin[jj] = bin[ii];
                        ++ii;
                    }
                    /*display(charBin, 8);*/
                    /* Convert every 8 bits to ascii because 8 bits represents each character */
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
        fclose(readPtr); readPtr = NULL;
        fclose(writePtr); writePtr = NULL;
    }
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
