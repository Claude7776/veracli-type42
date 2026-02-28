#include <openssl/evp.h>
#include <string.h>
#include "config.h"
#include "crypto.h"

/*
** AES-256-GCM encryption
** Return 1 on success, 0 on failure
*/

int aes_gcm_encrypt(const uint8_t *key, size_t key_len,
    const uint8_t *iv, size_t iv_len,
    const uint8_t *plaintext, size_t pt_len,
    uint8_t *ciphertext,
    uint8_t *tag, size_t tag_len)
{
    EVP_CIPHER_CTX *ctx;
    int len, ct_len;
    int ret;

    if (!key || !iv || !plaintext || !ciphertext || !tag)
        return (0);
    ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
        return (0);
    ret = EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL);
    if (ret != 1)
        goto fail;
    ret = EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, iv_len, NULL);
    if (ret != 1)
        goto fail;
    ret = EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv);
    if (ret != 1)
        goto fail;
    ret = EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, pt_len);
    if (ret != 1)
        goto fail;
    ct_len = len;
    ret = EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    if (ret != 1)
        goto fail;
    ct_len += len;
    ret = EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, tag_len, tag);
    if (ret != 1)
        goto fail;
    EVP_CIPHER_CTX_free(ctx);
    return (1);

fail:
    EVP_CIPHER_CTX_free(ctx);
    return (0);
}

/*
** AES-256-GCM decryption
** Return 1 on success, 0 on failure
*/

int aes_gcm_decrypt(const uint8_t *key, size_t key_len,
    const uint8_t *iv, size_t iv_len,
    const uint8_t *ciphertext, size_t ct_len,
    const uint8_t *tag, size_t tag_len,
    uint8_t *plaintext)
{
    EVP_CIPHER_CTX *ctx;
    int len, pt_len;
    int ret;

    if (!key || !iv || !ciphertext || !plaintext || !tag)
        return (0);
    ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
        return (0);
    ret = EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL);
    if (ret != 1)
        goto fail;
    ret = EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, iv_len, NULL);
    if (ret != 1)
        goto fail;
    ret = EVP_DecryptInit_ex(ctx, NULL, NULL, key, iv);
    if (ret != 1)
        goto fail;
    ret = EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ct_len);
    if (ret != 1)
        goto fail;
    pt_len = len;
    ret = EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, tag_len,
        (void *)tag);
    if (ret != 1)
        goto fail;
    ret = EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    if (ret != 1)
        goto fail;
    pt_len += len;
    EVP_CIPHER_CTX_free(ctx);
    return (1);

fail:
    EVP_CIPHER_CTX_free(ctx);
    return (0);
}
