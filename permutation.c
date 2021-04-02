#include <stdlib.h>
#include "permutation.h"
#include "file.h"

int **getInitialPermutation()
{
    int row = 8, col = 8;
    int i;

    int **ip = calloc(sizeof(int), row);

    for ( i = 0; i < row; ++i )
        ip[i] = calloc(sizeof(int), col); 

    read( "ip.txt", ip, row, col );
}
