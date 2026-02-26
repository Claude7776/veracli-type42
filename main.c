#include <stdio.h>
#include <string.h>
#include "crypto.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Usage:\n");
        printf("./veracli encrypt fichier\n");
        printf("./veracli decrypt fichier.enc\n");
        return 1;
    }

    if (strcmp(argv[1], "encrypt") == 0)
        return encrypt_file(argv[2]);
    else if (strcmp(argv[1], "decrypt") == 0)
        return decrypt_file(argv[2]);
    else
    {
        printf("Commande inconnue\n");
        return 1;
    }
}
