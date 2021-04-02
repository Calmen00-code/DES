#include <stdio.h>
#include "conversion.h"
#include "header.h"
#include "file.h"

void readNPermute( char fileName[], int *arr )
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
        ascii = i = 0;

        ch = fgetc(readPtr);

        /* ASSERTION: i = 64 OR file reading reaches the end */
        while ( i < IN_BITS && ch != EOF )
        {
            /* ascii is to be converted to binary for encryption */
            ascii = (int)(fgetc(readPtr));
            binaryConversion( &i, arr, ascii );

            if ( i == IN_BITS )
            {
                i = 0;
                /* Permutation here */
            }
            ch = fgetc(readPtr);
        }
        
        fclose(readPtr); readPtr = NULL;
    }
}

void readTable( char fileName[], int **table, int row, int col )
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
        }
    }
}