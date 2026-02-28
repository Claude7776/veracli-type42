#ifndef CONFIG_H
# define CONFIG_H

# include <stdint.h>

/*
** ============================================================
**                VERACLI GLOBAL CONFIGURATION
** ============================================================
*/

/* File format */
# define VERACLI_MAGIC       "VERACLI2"
# define VERACLI_MAGIC_SIZE  8
# define VERACLI_VERSION     0x01

/* KDF identifiers */
# define KDF_ARGON2ID        0x01

/* Crypto sizes */
# define SALT_SIZE           16
# define AES_KEY_SIZE        32
# define GCM_IV_SIZE         12
# define GCM_TAG_SIZE        16

/* Argon2id parameters */
# define ARGON2_TIME_COST    3
# define ARGON2_MEMORY_COST  65536
# define ARGON2_PARALLELISM  1

/* Security limits */
# define MAX_PASSWORD_LEN    256
# define MAX_FILE_SIZE       (1024ULL * 1024ULL * 1024ULL) 

/* Header size (fixed part only) */
# define HEADER_FIXED_SIZE   16

#endif
