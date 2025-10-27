#include "des.h"
#include "des_tables.h"
#include "utils.h"
#include <string.h>

// Helper function: Feistel function
static uint32_t feistel(uint32_t right, uint64_t subkey) {
    // Expand R from 32 to 48 bits
    // Shift right to align to MSB for permutation
    uint64_t r64 = ((uint64_t)right) << 32;
    uint64_t expanded = permute(r64, E, 48);
    
    // XOR with subkey (both are 48-bit values aligned to MSB)
    uint64_t xored = expanded ^ subkey;
    
    // S-box substitution - process 8 groups of 6 bits
    uint32_t sbox_output = 0;
    for (int i = 0; i < 8; i++) {
        // Extract 6 bits for this S-box (from MSB)
        int shift = 58 - (i * 6);  // 58, 52, 46, 40, 34, 28, 22, 16
        uint8_t six_bits = (xored >> shift) & 0x3F;
        
        // Calculate row (bits 0 and 5) and column (bits 1-4)
        int row = ((six_bits & 0x20) >> 4) | (six_bits & 0x01);
        int col = (six_bits & 0x1E) >> 1;
        
        // Get S-box output (4 bits)
        uint8_t sbox_val = S[i][row][col];
        
        // Place in output (from MSB)
        sbox_output |= ((uint32_t)sbox_val) << (28 - i * 4);
    }
    
    // P-box permutation
    uint64_t sbox64 = ((uint64_t)sbox_output) << 32;
    uint64_t permuted = permute(sbox64, P, 32);
    
    return (uint32_t)(permuted >> 32);
}

void des_key_schedule(uint64_t key, uint64_t round_keys[16]) {
    // PC1 permutation (64 bits -> 56 bits)
    uint64_t permuted_key = permute(key, PC1, 56);
    
    // Split into C0 and D0 (28 bits each)
    // After permutation, 56 bits are aligned to MSB
    uint32_t C = (uint32_t)(permuted_key >> 36) & 0x0FFFFFFF;
    uint32_t D = (uint32_t)(permuted_key >> 8) & 0x0FFFFFFF;
    
    // Generate 16 subkeys
    for (int round = 0; round < 16; round++) {
        // Left circular shift (28-bit rotation)
        int shifts = LEFT_SHIFTS[round];
        C = ((C << shifts) | (C >> (28 - shifts))) & 0x0FFFFFFF;
        D = ((D << shifts) | (D >> (28 - shifts))) & 0x0FFFFFFF;
        
        // Combine C and D (56 bits total, aligned to MSB)
        uint64_t combined = (((uint64_t)C) << 36) | (((uint64_t)D) << 8);
        
        // Apply PC2 to get round key (56 bits -> 48 bits)
        round_keys[round] = permute(combined, PC2, 48);
    }
}

void des_encrypt_block(uint64_t plaintext, uint64_t key, uint64_t *ciphertext) {
    uint64_t round_keys[16];
    
    // Generate round keys
    des_key_schedule(key, round_keys);
    
    // Initial permutation
    uint64_t permuted = permute(plaintext, IP, 64);
    
    // Split into L0 and R0 (32 bits each)
    uint32_t L = (uint32_t)(permuted >> 32);
    uint32_t R = (uint32_t)(permuted & 0xFFFFFFFF);
    
    // 16 rounds
    for (int round = 0; round < 16; round++) {
        uint32_t temp = R;
        uint32_t f_result = feistel(R, round_keys[round]);
        R = L ^ f_result;
        L = temp;
    }
    
    // Combine R16 and L16 (note the swap)
    uint64_t combined = (((uint64_t)R) << 32) | L;
    
    // Final permutation
    *ciphertext = permute(combined, FP, 64);
}

void des_decrypt_block(uint64_t ciphertext, uint64_t key, uint64_t *plaintext) {
    uint64_t round_keys[16];
    
    // Generate round keys
    des_key_schedule(key, round_keys);
    
    // Initial permutation
    uint64_t permuted = permute(ciphertext, IP, 64);
    
    // Split into L0 and R0 (32 bits each)
    uint32_t L = (uint32_t)(permuted >> 32);
    uint32_t R = (uint32_t)(permuted & 0xFFFFFFFF);
    
    // 16 rounds with reversed key order
    for (int round = 0; round < 16; round++) {
        uint32_t temp = R;
        uint32_t f_result = feistel(R, round_keys[15 - round]);
        R = L ^ f_result;
        L = temp;
    }
    
    // Combine R16 and L16 (note the swap)
    uint64_t combined = (((uint64_t)R) << 32) | L;
    
    // Final permutation
    *plaintext = permute(combined, FP, 64);
}

void des_encrypt(const uint64_t *plaintext, uint64_t key, uint64_t *ciphertext, size_t num_blocks) {
    // Generate round keys once for all blocks
    uint64_t round_keys[16];
    des_key_schedule(key, round_keys);
    
    // Encrypt each block
    for (size_t i = 0; i < num_blocks; i++) {
        // Initial permutation
        uint64_t permuted = permute(plaintext[i], IP, 64);
        
        // Split into L0 and R0 (32 bits each)
        uint32_t L = (uint32_t)(permuted >> 32);
        uint32_t R = (uint32_t)(permuted & 0xFFFFFFFF);
        
        // 16 rounds
        for (int round = 0; round < 16; round++) {
            uint32_t temp = R;
            uint32_t f_result = feistel(R, round_keys[round]);
            R = L ^ f_result;
            L = temp;
        }
        
        // Combine R16 and L16 (note the swap)
        uint64_t combined = (((uint64_t)R) << 32) | L;
        
        // Final permutation
        ciphertext[i] = permute(combined, FP, 64);
    }
}

void des_decrypt(const uint64_t *ciphertext, uint64_t key, uint64_t *plaintext, size_t num_blocks) {
    // Generate round keys once for all blocks
    uint64_t round_keys[16];
    des_key_schedule(key, round_keys);
    
    // Decrypt each block
    for (size_t i = 0; i < num_blocks; i++) {
        // Initial permutation
        uint64_t permuted = permute(ciphertext[i], IP, 64);
        
        // Split into L0 and R0 (32 bits each)
        uint32_t L = (uint32_t)(permuted >> 32);
        uint32_t R = (uint32_t)(permuted & 0xFFFFFFFF);
        
        // 16 rounds with reversed key order
        for (int round = 0; round < 16; round++) {
            uint32_t temp = R;
            uint32_t f_result = feistel(R, round_keys[15 - round]);
            R = L ^ f_result;
            L = temp;
        }
        
        // Combine R16 and L16 (note the swap)
        uint64_t combined = (((uint64_t)R) << 32) | L;
        
        // Final permutation
        plaintext[i] = permute(combined, FP, 64);
    }
}
