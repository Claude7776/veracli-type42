#ifndef CRYPTO_H
# define CRYPTO_H

# include <stdint.h>
# include <stddef.h>

/*
** ============================================================
**                AES-256-GCM ENCRYPT / DECRYPT
** ============================================================
*/

int aes_gcm_encrypt(const uint8_t *key, size_t key_len,
    const uint8_t *iv, size_t iv_len,
    const uint8_t *plaintext, size_t pt_len,
    uint8_t *ciphertext,
    uint8_t *tag, size_t tag_len);

int aes_gcm_decrypt(const uint8_t *key, size_t key_len,
    const uint8_t *iv, size_t iv_len,
    const uint8_t *ciphertext, size_t ct_len,
    const uint8_t *tag, size_t tag_len,
    uint8_t *plaintext);

#endif
