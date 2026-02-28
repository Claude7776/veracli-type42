#include <string.h>
#include <stdlib.h>
#include "header.h"

void header_init(veracli_header_t *header)
{
    int i;

    if (!header)
        return;
    memcpy(header->magic, VERACLI_MAGIC, VERACLI_MAGIC_SIZE);
    header->version  = VERACLI_VERSION;
    header->kdf_id   = KDF_ARGON2ID;
    header->salt_len = SALT_SIZE;
    header->iv_len   = GCM_IV_SIZE;
    header->tag_len  = GCM_TAG_SIZE;
    i = 0;
    while (i < 3)
    {
        header->reserved[i] = 0;
        i++;
    }
}

int header_validate(const veracli_header_t *header)
{
    if (!header)
        return (0);
    if (memcmp(header->magic, VERACLI_MAGIC, VERACLI_MAGIC_SIZE) != 0)
        return (0);
    if (header->version != VERACLI_VERSION)
        return (0);
    if (header->kdf_id != KDF_ARGON2ID)
        return (0);
    if (header->salt_len != SALT_SIZE)
        return (0);
    if (header->iv_len != GCM_IV_SIZE)
        return (0);
    if (header->tag_len != GCM_TAG_SIZE)
        return (0);
    return (1);
}

int header_write(FILE *fp, const veracli_header_t *header)
{
    if (!fp || !header)
        return (0);
    if (fwrite(header, sizeof(veracli_header_t), 1, fp) != 1)
        return (0);
    return (1);
}

int header_read(FILE *fp, veracli_header_t *header)
{
    if (!fp || !header)
        return (0);
    if (fread(header, sizeof(veracli_header_t), 1, fp) != 1)
        return (0);
    return (1);
}
