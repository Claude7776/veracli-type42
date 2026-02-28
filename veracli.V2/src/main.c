#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "crypto.h"
#include "header.h"
#include "kdf.h"
#include "utils.h"

static	void usage(void)
{
	printf("Usage:\n");
	printf("	veracli enc <infile> <outfile> <password>\n");
	printf("	veracli dec <infile> <outfile> <password>\n");	
}

int	main(int argc, char **argv)
{
	FILE	*fp_in;
	FILE	*fp_out;
	uint8_t salt[SALT_SIZE];
	uint8_t key[AES_KEY_SIZE];
	uint8_t iv[GCM_IV_SIZE];
	uint8_t tag[GCM_TAG_SIZE];
	veracli_header_t header;
	uint8_t *buffer;
	size_t filesize;

	if (argc != 5)
	{
		usage();
		return (1);
	}

	if (strcmp(argv[1], "enc") != 0 && strcmp(argv[1], "dec") != 0)
    {
        usage();
        return (1);
    }

	fp_in = fopen(argv[2], "rb");
	if (!fp_in)
	{
		perror("fopen input");
		return (1);
	}
	fseek(fp_in, 0, SEEK_END);
	filesize = ftell(fp_in);
	rewind(fp_in);
	if (filesize > MAX_FILE_SIZE)
	{
		printf("File too big\n");
		fclose(fp_in);
		return (1);
	}

	buffer = malloc(filesize);
	if (!buffer)
	{
		fclose(fp_in);
		return (1);
	}
	fread(buffer, 1, filesize, fp_in);
	fclose(fp_in);

	header_init(&header);
    generate_random(salt, SALT_SIZE);
    generate_random(iv, GCM_IV_SIZE);

    if (!derive_key(argv[4], strlen(argv[4]), salt, SALT_SIZE,
        key, AES_KEY_SIZE))
    {
        printf("Key derivation failed\n");
        free(buffer);
        return (1);
    }

    fp_out = fopen(argv[3], "wb");
    if (!fp_out)
    {
        perror("fopen output");
        free(buffer);
        return (1);
    }

    if (!header_write(fp_out, &header))
    {
        printf("Header write failed\n");
        free(buffer);
        fclose(fp_out);
        return (1);
    }

    if (strcmp(argv[1], "enc") == 0)
    {
        if (!aes_gcm_encrypt(key, AES_KEY_SIZE, iv, GCM_IV_SIZE,
            buffer, filesize, buffer, tag, GCM_TAG_SIZE))
        {
            printf("Encryption failed\n");
            free(buffer);
            fclose(fp_out);
            return (1);
        }
    }

    fwrite(buffer, 1, filesize, fp_out);
    fclose(fp_out);
    free(buffer);
    printf("Operation completed successfully\n");
    return (0);
}
