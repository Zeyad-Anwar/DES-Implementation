#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>
#include "utils.h"
#include "des_tables.h"

static void test_get_bit64(void) {
    printf("\n=== Testing get_bit64 ===\n");

    const uint64_t value = 0x8000000000000001ULL;

    assert(get_bit64(value, 0) == 1);
    assert(get_bit64(value, 63) == 1);
    assert(get_bit64(value, 1) == 0);
    assert(get_bit64(value, 62) == 0);

    printf("✓ get_bit64 tests passed\n");
}

static void test_permute_identity(void) {
    printf("\n=== Testing permute (identity) ===\n");

    uint8_t identity[64];
    for (int i = 0; i < 64; i++) {
        identity[i] = (uint8_t)(i + 1);
    }

    const uint64_t input = 0x0123456789ABCDEFULL;
    const uint64_t output = permute(input, identity, 64);

    assert(output == input);

    printf("✓ permute identity test passed\n");
}

static void test_permute_truncate(void) {
    printf("\n=== Testing permute (upper 32 bits) ===\n");

    uint8_t top32[32];
    for (int i = 0; i < 32; i++) {
        top32[i] = (uint8_t)(i + 1);
    }

    const uint64_t input = 0xFEDCBA9876543210ULL;
    const uint64_t output = permute(input, top32, 32);
    const uint64_t expected = input & 0xFFFFFFFF00000000ULL;

    assert(output == expected);

    printf("✓ permute partial-width test passed\n");
}

static void test_permute_with_ip(void) {
    printf("\n=== Testing permute with IP table ===\n");

    const uint64_t input = 0x0123456789ABCDEFULL;
    const uint64_t output = permute(input, IP, 64);

    printf("Input:    0x%016" PRIX64 "\n", input);
    printf("Output:   0x%016" PRIX64 "\n", output);
    
    // Test that IP followed by FP returns the original value
    const uint64_t reversed = permute(output, FP, 64);
    
    printf("Reversed: 0x%016" PRIX64 "\n", reversed);
    
    assert(reversed == input);

    printf("✓ permute IP/FP inverse test passed\n");
}

static void test_hex_to_uint64(void) {
    printf("\n=== Testing hex_to_uint64 ===\n");

    uint64_t value = 0;
    int result = hex_to_uint64("0123456789ABCDEF", &value);

    assert(result == 0);
    assert(value == 0x0123456789ABCDEFULL);

    printf("✓ hex_to_uint64 conversion test passed\n");
}

static void test_hex_to_uint64_invalid(void) {
    printf("\n=== Testing hex_to_uint64 invalid input ===\n");

    uint64_t value = 0;
    int result = hex_to_uint64("01234G6789ABCDEF", &value);

    assert(result == -1);

    printf("✓ hex_to_uint64 invalid input test passed\n");
}

int main(void) {
    printf("========================================\n");
    printf("Utility Functions Test Suite\n");
    printf("========================================\n");

    test_get_bit64();
    test_permute_identity();
    test_permute_truncate();
    test_permute_with_ip();
    test_hex_to_uint64();
    test_hex_to_uint64_invalid();

    printf("\n========================================\n");
    printf("All utility tests passed!\n");
    printf("========================================\n");

    return 0;
}
