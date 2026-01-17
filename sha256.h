#ifndef SHA256_H
#define SHA256_H

//surprising bare bones needed for the Sha256 implementation.
#include <stdint.h>
#include <string.h>

#define SHA256_BLOCK_SIZE 32

typedef struct {
    uint8_t data[64];
    uint32_t datalen;
    uint64_t bitlen;
    uint32_t state[8];
} SHA256_CTX;

//Function declarations for Sha256 useability.
void sha256_init(SHA256_CTX *ctx);
void sha256_update(SHA256_CTX *ctx, const uint8_t data[], size_t len);
void sha256_final(SHA256_CTX *ctx, uint8_t hash[]);
void sha256_string(const char *str, uint8_t hash[SHA256_BLOCK_SIZE]);
void sha256_to_string(const uint8_t hash[SHA256_BLOCK_SIZE], char output[65]);

#endif