#ifndef DES_H
#define DES_H

#include <stdint.h>

/* DES block size in bytes */
#define DES_BLOCK_SIZE 8

/* DES key size in bytes */
#define DES_KEY_SIZE 8

/**
 * Encrypts a single 64-bit block using DES algorithm
 * @param plaintext: 8-byte input block
 * @param key: 8-byte key (56 effective bits, 8 parity bits)
 * @param ciphertext: 8-byte output block
 */
void des_encrypt(const uint8_t *plaintext, const uint8_t *key, uint8_t *ciphertext);

/**
 * Decrypts a single 64-bit block using DES algorithm
 * @param ciphertext: 8-byte input block
 * @param key: 8-byte key (56 effective bits, 8 parity bits)
 * @param plaintext: 8-byte output block
 */
void des_decrypt(const uint8_t *ciphertext, const uint8_t *key, uint8_t *plaintext);

/**
 * Generates 16 round keys from the main key
 * @param key: 8-byte main key
 * @param round_keys: Array to store 16 round keys (48 bits each)
 */
void des_key_schedule(const uint8_t *key, uint64_t *round_keys);

#endif /* DES_H */
