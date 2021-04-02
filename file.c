#include <stdio.h>
#include "file.h"

void read( int** ip, char fileName[], int row, int col )
{
    FILE *readPtr = NULL;

    readPtr = fopen(fileName, "r");
    if ( readPtr
