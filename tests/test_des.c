#include <stdio.h>
#include <string.h>
#include "des.h"
#include "utils.h"
#include "test_vectors.h"

static int tests_passed = 0;
static int tests_failed = 0;

void test_encryption() {
    printf("\n=== Testing DES Encryption ===\n");
    
    for (size_t i = 0; i < NUM_TEST_VECTORS; i++) {
        const test_vector_t *tv = &test_vectors[i];
        uint8_t ciphertext[DES_BLOCK_SIZE];
        
        printf("\nTest: %s\n", tv->name);
        printf("Plaintext:  ");
        print_hex(tv->plaintext, DES_BLOCK_SIZE);
        printf("Key:        ");
        print_hex(tv->key, DES_KEY_SIZE);
        
        des_encrypt(tv->plaintext, tv->key, ciphertext);
        
        printf("Got:        ");
        print_hex(ciphertext, DES_BLOCK_SIZE);
        printf("Expected:   ");
        print_hex(tv->expected_ciphertext, DES_BLOCK_SIZE);
        
        if (memcmp(ciphertext, tv->expected_ciphertext, DES_BLOCK_SIZE) == 0) {
            printf("✓ PASS\n");
            tests_passed++;
        } else {
            printf("✗ FAIL\n");
            tests_failed++;
        }
    }
}

void test_decryption() {
    printf("\n=== Testing DES Decryption ===\n");
    
    for (size_t i = 0; i < NUM_TEST_VECTORS; i++) {
        const test_vector_t *tv = &test_vectors[i];
        uint8_t decrypted[DES_BLOCK_SIZE];
        
        printf("\nTest: %s\n", tv->name);
        printf("Ciphertext: ");
        print_hex(tv->expected_ciphertext, DES_BLOCK_SIZE);
        printf("Key:        ");
        print_hex(tv->key, DES_KEY_SIZE);
        
        des_decrypt(tv->expected_ciphertext, tv->key, decrypted);
        
        printf("Got:        ");
        print_hex(decrypted, DES_BLOCK_SIZE);
        printf("Expected:   ");
        print_hex(tv->plaintext, DES_BLOCK_SIZE);
        
        if (memcmp(decrypted, tv->plaintext, DES_BLOCK_SIZE) == 0) {
            printf("✓ PASS\n");
            tests_passed++;
        } else {
            printf("✗ FAIL\n");
            tests_failed++;
        }
    }
}

void test_round_trip() {
    printf("\n=== Testing Encryption/Decryption Round Trip ===\n");
    
    for (size_t i = 0; i < NUM_TEST_VECTORS; i++) {
        const test_vector_t *tv = &test_vectors[i];
        uint8_t ciphertext[DES_BLOCK_SIZE];
        uint8_t decrypted[DES_BLOCK_SIZE];
        
        printf("\nTest: %s\n", tv->name);
        
        des_encrypt(tv->plaintext, tv->key, ciphertext);
        des_decrypt(ciphertext, tv->key, decrypted);
        
        if (memcmp(tv->plaintext, decrypted, DES_BLOCK_SIZE) == 0) {
            printf("✓ PASS - Round trip successful\n");
            tests_passed++;
        } else {
            printf("✗ FAIL - Round trip failed\n");
            tests_failed++;
        }
    }
}

int main() {
    printf("========================================\n");
    printf("DES Implementation Test Suite\n");
    printf("========================================\n");
    
    test_encryption();
    test_decryption();
    test_round_trip();
    
    printf("\n========================================\n");
    printf("Test Results:\n");
    printf("  Passed: %d\n", tests_passed);
    printf("  Failed: %d\n", tests_failed);
    printf("  Total:  %d\n", tests_passed + tests_failed);
    printf("========================================\n");
    
    return (tests_failed == 0) ? 0 : 1;
}
