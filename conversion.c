#include "conversion.h"
#include <stdio.h>

void binaryConversion( int num, char *str )
{
    int i;
    i = 7;

    while ( i > 0 && num / 2 != 0 )
    {
        if ( num % 2 == 0 )
            str[i] = '0';
        else
            str[i] = '1';
        num /= 2;
        --i;
    }
    str[0] = '0';
}
