#include <stdlib.h>
#include "permutation.h"
#include "file.h"

void initialPermutation( 

int **getInitialPermutation()
{
    int row = ROW_IP, col = COL_IP;
    int i;

    int **ip = calloc(sizeof(int), row);

    for ( i = 0; i < row; ++i )
        ip[i] = calloc(sizeof(int), col); 

    readTable( "ip.txt", ip, row, col );
}
