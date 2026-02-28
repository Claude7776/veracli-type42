#ifndef HEADER_H
# define HEADER_H

# include <stdint.h>
# include <stdio.h>
# include "config.h"

typedef struct __attribute__((packed))
{
    uint8_t magic[VERACLI_MAGIC_SIZE];
    uint8_t version;
    uint8_t kdf_id;
    uint8_t salt_len;
    uint8_t iv_len;
    uint8_t tag_len;
    uint8_t reserved[3];
}   veracli_header_t;

void header_init(veracli_header_t *header);
int  header_validate(const veracli_header_t *header);
int  header_write(FILE *fp, const veracli_header_t *header);
int  header_read(FILE *fp, veracli_header_t *header);

#endif
