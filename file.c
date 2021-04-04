#include <stdio.h>
#include "permutation.h"
#include "conversion.h"
#include "header.h"
#include "file.h"
#include "encrypt.h"

void readNPermute( char fileName[], int *arr, int keyLen )
{
    FILE *readPtr = NULL;
    char ch;
    int i;
    int ascii;

    readPtr = fopen(fileName, "r");

    if ( readPtr == NULL )
        perror("Error while reading file ");
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
            binaryConversion( i, arr, ascii );

            /* Each character in ascii = 7 bits + 1 '0' bit infront = 8 bits */
            i += 8;     

            /* Send the current block for permutation and next block to come in */
            if ( i >= IN_BITS )
            {
                i = 7;  /* Reset to initial 7 since the bits is finished at 64 bits */
                initialPermutation( arr );
                encrypt( arr, keyLen );
            }
            ch = fgetc(readPtr);
        }
        fclose(readPtr); readPtr = NULL;
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
