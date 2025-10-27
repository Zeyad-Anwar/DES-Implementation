#ifndef DES_H
#define DES_H

#include <stdint.h>
#include <stddef.h>

/* DES block size in bytes */
#define DES_BLOCK_SIZE 8

/* DES key size in bytes */
#define DES_KEY_SIZE 8

/**
 * Encrypts multiple 64-bit blocks using DES algorithm
 * @param plaintext: Array of 64-bit input blocks
 * @param key: 64-bit key (56 effective bits, 8 parity bits)
 * @param ciphertext: Array to store 64-bit output blocks
 * @param num_blocks: Number of blocks to encrypt
 */
void des_encrypt(const uint64_t *plaintext, uint64_t key, uint64_t *ciphertext, size_t num_blocks);

/**
 * Decrypts multiple 64-bit blocks using DES algorithm
 * @param ciphertext: Array of 64-bit input blocks
 * @param key: 64-bit key (56 effective bits, 8 parity bits)
 * @param plaintext: Array to store 64-bit output blocks
 * @param num_blocks: Number of blocks to decrypt
 */
void des_decrypt(const uint64_t *ciphertext, uint64_t key, uint64_t *plaintext, size_t num_blocks);

/**
 * Encrypts a single 64-bit block using DES algorithm
 * @param plaintext: 64-bit input block
 * @param key: 64-bit key (56 effective bits, 8 parity bits)
 * @param ciphertext: Pointer to store 64-bit output block
 */
void des_encrypt_block(uint64_t plaintext, uint64_t key, uint64_t *ciphertext);

/**
 * Decrypts a single 64-bit block using DES algorithm
 * @param ciphertext: 64-bit input block
 * @param key: 64-bit key (56 effective bits, 8 parity bits)
 * @param plaintext: Pointer to store 64-bit output block
 */
void des_decrypt_block(uint64_t ciphertext, uint64_t key, uint64_t *plaintext);

/**
 * Generates 16 round keys from the main key
 * @param key: 64-bit main key
 * @param round_keys: Array to store 16 round keys (48 bits each)
 */
void des_key_schedule(uint64_t key, uint64_t round_keys[16]);

#endif /* DES_H */
