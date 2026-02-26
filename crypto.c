#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

#define SALT_SIZE 16
#define IV_SIZE 16
#define KEY_SIZE 32
#define ITERATIONS 200000

void derive_key(const char *password, unsigned char *salt, unsigned char *key)
{
    PKCS5_PBKDF2_HMAC(password, strlen(password),
                      salt, SALT_SIZE,
                      ITERATIONS,
                      EVP_sha256(),
                      KEY_SIZE,
                      key);
}

int encrypt_file(const char *filename)
{
    FILE *in = fopen(filename, "rb");
    if (!in) return 1;

    fseek(in, 0, SEEK_END);
    long filesize = ftell(in);
    rewind(in);

    unsigned char *plaintext = malloc(filesize);
    fread(plaintext, 1, filesize, in);
    fclose(in);

    char password[256];
    printf("Mot de passe: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    unsigned char salt[SALT_SIZE];
    unsigned char iv[IV_SIZE];
    unsigned char key[KEY_SIZE];

    RAND_bytes(salt, SALT_SIZE);
    RAND_bytes(iv, IV_SIZE);
    derive_key(password, salt, key);

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    unsigned char *ciphertext = malloc(filesize + EVP_MAX_BLOCK_LENGTH);
    int len, ciphertext_len;

    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, filesize);
    ciphertext_len = len;

    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    char outname[256];
    snprintf(outname, sizeof(outname), "%s.enc", filename);
    FILE *out = fopen(outname, "wb");

    fwrite(salt, 1, SALT_SIZE, out);
    fwrite(iv, 1, IV_SIZE, out);
    fwrite(ciphertext, 1, ciphertext_len, out);

    fclose(out);
    free(plaintext);
    free(ciphertext);

    printf("Fichier chiffré: %s\n", outname);
    return 0;
}

int decrypt_file(const char *filename)
{
    FILE *in = fopen(filename, "rb");
    if (!in) return 1;

    unsigned char salt[SALT_SIZE];
    unsigned char iv[IV_SIZE];

    fread(salt, 1, SALT_SIZE, in);
    fread(iv, 1, IV_SIZE, in);

    fseek(in, 0, SEEK_END);
    long filesize = ftell(in);
    fseek(in, SALT_SIZE + IV_SIZE, SEEK_SET);

    long ciphertext_size = filesize - SALT_SIZE - IV_SIZE;
    unsigned char *ciphertext = malloc(ciphertext_size);
    fread(ciphertext, 1, ciphertext_size, in);
    fclose(in);

    char password[256];
    printf("Mot de passe: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    unsigned char key[KEY_SIZE];
    derive_key(password, salt, key);

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    unsigned char *plaintext = malloc(ciphertext_size);
    int len, plaintext_len;

    EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_size);
    plaintext_len = len;

    if (EVP_DecryptFinal_ex(ctx, plaintext + len, &len) <= 0)
    {
        printf("Mot de passe incorrect ou fichier corrompu\n");
        return 1;
    }

    plaintext_len += len;
    EVP_CIPHER_CTX_free(ctx);

    char outname[256];
    snprintf(outname, sizeof(outname), "%s.dec", filename);
    FILE *out = fopen(outname, "wb");
    fwrite(plaintext, 1, plaintext_len, out);
    fclose(out);

    free(ciphertext);
    free(plaintext);

    printf("Fichier déchiffré: %s\n", outname);
    return 0;
}
