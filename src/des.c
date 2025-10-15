#include "des.h"
#include "des_tables.h"
#include "utils.h"
#include <string.h>

void des_encrypt(const uint8_t *plaintext, const uint8_t *key, uint8_t *ciphertext) {
    // TODO: Implement DES encryption
    // 1. Initial permutation
    // 2. 16 rounds of Feistel structure
    // 3. Final permutation
}

void des_decrypt(const uint8_t *ciphertext, const uint8_t *key, uint8_t *plaintext) {
    // TODO: Implement DES decryption
    // Same as encryption but with reversed round key order
}

void des_key_schedule(const uint8_t *key, uint64_t *round_keys) {
    // TODO: Implement key schedule generation
    // 1. Apply PC1 permutation
    // 2. Split into left and right halves
    // 3. For each round: shift, combine, apply PC2
}
