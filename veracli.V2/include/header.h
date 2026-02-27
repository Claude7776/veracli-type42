#ifndef HEADER_H
#define HEADER_H

#include <stdint.h>

#define MAGIC_SIZE 8
#define RESERVED_SIZE 3

#define KDF_ARGON2ID 0x01

typedef struct __attribute__((packed))
{
    uint8_t  magic[MAGIC_SIZE];  // "VERACLI2"
    uint8_t  version;            // 0x01
    uint8_t  kdf_id;             // 0x01 = Argon2id
    uint8_t  salt_len;           // usually 16
    uint8_t  iv_len;             // usually 12 (GCM)
    uint8_t  tag_len;            // usually 16
    uint8_t  reserved[RESERVED_SIZE];
} veracli_header_t;

#endif
