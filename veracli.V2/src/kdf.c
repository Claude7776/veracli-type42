#include <string.h>
#include <argon2.h>
#include "config.h"
#include "kdf.h"

int derive_key(const char *password, size_t pass_len,
    const uint8_t *salt, size_t salt_len,
    uint8_t *key, size_t key_len)
{
    int ret;

    if (!password || !salt || !key)
        return (0);
    if (pass_len == 0 || salt_len == 0 || key_len == 0)
        return (0);
    ret = argon2id_hash_raw(ARGON2_TIME_COST,
        ARGON2_MEMORY_COST,
        ARGON2_PARALLELISM,
        password,
        pass_len,
        salt,
        salt_len,
        key,
        key_len);
    if (ret != ARGON2_OK)
        return (0);
    return (1);
}
