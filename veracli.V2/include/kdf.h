#ifndef KDF_H
# define KDF_H

# include <stdint.h>
# include <stddef.h>

int derive_key(const char *password, size_t pass_len,
    const uint8_t *salt, size_t salt_len,
    uint8_t *key, size_t key_len);

#endif
