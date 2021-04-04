#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "conversion.h"
#include "header.h"
#include "file.h"

int main(int argc, char *argv[])
{
    int *arr = NULL;
    int keyLen;
    /* int i; , j;*/
    char cipherFile[STR] = "";

    if ( argc != 2 )
        printf("To run the program: ./main [*.txt]\n");
    else
    {
        keyLen = 0;
        printf("Key Length: ");
        scanf("%d", &keyLen);
        arr = calloc(sizeof(int), IN_BITS);
        strcpy( cipherFile, argv[1] );
        readNPermute( cipherFile, arr, keyLen );

        free(arr); arr = NULL;
    }
    return 0;
}
