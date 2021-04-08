#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "conversion.h"
#include "header.h"
#include "file.h"

int main(int argc, char *argv[])
{
    int *cipherBit = NULL;
    char key[STR] = "";
    /* int i; , j;*/
    char cipherFile[STR] = "";

    if ( argc != 2 )
        printf("To run the program: ./main [*.txt]\n");
    else
    {
        printf("Key: ");
        scanf("%s", key);
        cipherBit = calloc(sizeof(int), IN_BITS);
        strcpy( cipherFile, argv[1] );
        readNEncrypt( cipherFile, cipherBit, key );
        

        free(cipherBit); cipherBit = NULL;
    }
    return 0;
}
