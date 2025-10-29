#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "des.h"
#include "utils.h"
#include "test_vectors.h"

static int tests_passed = 0;
static int tests_failed = 0;

static void log_block(const char *label, uint64_t value) {
    printf("%s: 0x%016" PRIX64 "\n", label, value);
}

static void record_result(int condition) {
    if (condition) {
        printf("✓ PASS\n");
        tests_passed++;
    } else {
        printf("✗ FAIL\n");
        tests_failed++;
    }
}

static void test_encryption_vectors(void) {
    printf("\n=== Testing DES Encryption Vectors ===\n");

    for (size_t i = 0; i < NUM_TEST_VECTORS; i++) {
        const test_vector_t *tv = &test_vectors[i];
        uint64_t ciphertext = 0;

        printf("\nTest: %s\n", tv->name);
        log_block("Plaintext", tv->plaintext);
        log_block("Key", tv->key);

        des_encrypt_block(tv->plaintext, tv->key, &ciphertext);

        log_block("Got", ciphertext);
        log_block("Expected", tv->expected_ciphertext);

        record_result(ciphertext == tv->expected_ciphertext);
    }
}

static void test_decryption_vectors(void) {
    printf("\n=== Testing DES Decryption Vectors ===\n");

    for (size_t i = 0; i < NUM_TEST_VECTORS; i++) {
        const test_vector_t *tv = &test_vectors[i];
        uint64_t plaintext = 0;

        printf("\nTest: %s\n", tv->name);
        log_block("Ciphertext", tv->expected_ciphertext);
        log_block("Key", tv->key);

        des_decrypt_block(tv->expected_ciphertext, tv->key, &plaintext);

        log_block("Got", plaintext);
        log_block("Expected", tv->plaintext);

        record_result(plaintext == tv->plaintext);
    }
}

static void test_round_trip(void) {
    printf("\n=== Testing Encryption/Decryption Round Trip ===\n");

    for (size_t i = 0; i < NUM_TEST_VECTORS; i++) {
        const test_vector_t *tv = &test_vectors[i];
        uint64_t ciphertext = 0;
        uint64_t decrypted = 0;

        printf("\nTest: %s\n", tv->name);

        des_encrypt_block(tv->plaintext, tv->key, &ciphertext);
        des_decrypt_block(ciphertext, tv->key, &decrypted);

        record_result(decrypted == tv->plaintext);
    }
}

static void test_multi_block_api(void) {
    printf("\n=== Testing Multi-block API ===\n");

    const uint64_t key = test_vectors[0].key;
    const uint64_t plaintext_blocks[] = {
        test_vectors[0].plaintext,
        test_vectors[1].plaintext,
        0x0F1E2D3C4B5A6978ULL
    };
    const size_t num_blocks = sizeof(plaintext_blocks) / sizeof(plaintext_blocks[0]);

    uint64_t expected_cipher[num_blocks];
    uint64_t cipher[num_blocks];
    uint64_t decrypted[num_blocks];

    for (size_t i = 0; i < num_blocks; i++) {
        des_encrypt_block(plaintext_blocks[i], key, &expected_cipher[i]);
    }

    des_encrypt(plaintext_blocks, key, cipher, num_blocks);
    des_decrypt(cipher, key, decrypted, num_blocks);

    int encryption_matches = (memcmp(cipher, expected_cipher, sizeof(cipher)) == 0);
    int decryption_matches = (memcmp(decrypted, plaintext_blocks, sizeof(decrypted)) == 0);

    record_result(encryption_matches && decryption_matches);
}

int main(void) {
    printf("========================================\n");
    printf("DES Implementation Test Suite\n");
    printf("========================================\n");

    test_encryption_vectors();
    test_decryption_vectors();
    test_round_trip();
    test_multi_block_api();

    printf("\n========================================\n");
    printf("Test Results:\n");
    printf("  Passed: %d\n", tests_passed);
    printf("  Failed: %d\n", tests_failed);
    printf("  Total:  %d\n", tests_passed + tests_failed);
    printf("========================================\n");

    return (tests_failed == 0) ? 0 : 1;
}
