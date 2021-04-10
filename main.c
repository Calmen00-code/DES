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
    int mode = 0;
    char plainFile[STR] = "", cipherFile[STR] = "";

    if ( argc != 3 )
    {
        printf("To run the program: ./main [mode] [*.txt]\n\n");
        printf("              Mode: 1 [Encrypt]\n");
        printf("              Mode: 2 [Decrypt]\n");
    }
    else
    {
        printf("Key: ");
        scanf("%s", key);
        mode = atoi(argv[1]);
        cipherBit = calloc(sizeof(int), IN_BITS);

        if ( mode == 1 )
        {
            strcpy( plainFile, argv[2] );
            readNEncrypt( plainFile, cipherBit, key );
        }
        else if ( mode == 2 )
        {
            strcpy( cipherFile, argv[2] );
            readNDecrypt( cipherFile, cipherBit, key );
        }
        else
            printf("Invalid mode\n");
        free(cipherBit); cipherBit = NULL;
    }
    return 0;
}
