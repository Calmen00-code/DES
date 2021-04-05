#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "conversion.h"
#include "header.h"
#include "file.h"

int main(int argc, char *argv[])
{
    int *arr = NULL;
    char key[STR] = "";
    /* int i; , j;*/
    char cipherFile[STR] = "";

    if ( argc != 2 )
        printf("To run the program: ./main [*.txt]\n");
    else
    {
        printf("Key: ");
        scanf("%s", key);
        arr = calloc(sizeof(int), IN_BITS);
        strcpy( cipherFile, argv[1] );
        readNPermute( cipherFile, arr, key );

        free(arr); arr = NULL;
    }
    return 0;
}
