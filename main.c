#include <stdio.h>
#include <stdlib.h>
#include "conversion.h"

int main()
{
    char BLUE[100] = "BLUE";
    char *str = NULL;
    int ascii = 0;
    /* char blue[100] = "blue"; */

    int i;
    str = malloc(sizeof(char) * 9);

    for ( i = 0; i < 8; ++i )
        str[i] = '0';
    str[8] = '\0';
    
    for ( i = 0; BLUE[i] != '\0'; ++i )
    {
        ascii = (int)(BLUE[i]);
        printf("ascii: %d\n", ascii);
        binaryConversion( ascii, str );
        printf("%c: %s\n", BLUE[i], str);
    }

    return 0;
}
