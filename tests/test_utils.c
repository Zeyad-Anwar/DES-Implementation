#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "utils.h"

void test_get_set_bit() {
    printf("\n=== Testing get_bit and set_bit ===\n");
    
    uint8_t data[1] = {0x00};
    
    // Set some bits
    set_bit(data, 0, 1);
    assert(data[0] == 0x80);
    assert(get_bit(data, 0) == 1);
    
    set_bit(data, 7, 1);
    assert(data[0] == 0x81);
    assert(get_bit(data, 7) == 1);
    
    set_bit(data, 0, 0);
    assert(data[0] == 0x01);
    assert(get_bit(data, 0) == 0);
    
    printf("✓ Bit manipulation tests passed\n");
}

void test_xor_bytes() {
    printf("\n=== Testing xor_bytes ===\n");
    
    uint8_t a[4] = {0xAA, 0xBB, 0xCC, 0xDD};
    uint8_t b[4] = {0x11, 0x22, 0x33, 0x44};
    uint8_t result[4];
    uint8_t expected[4] = {0xBB, 0x99, 0xFF, 0x99};
    
    xor_bytes(a, b, result, 4);
    
    assert(memcmp(result, expected, 4) == 0);
    
    printf("✓ XOR operation tests passed\n");
}

void test_hex_conversion() {
    printf("\n=== Testing hex_to_bytes ===\n");
    
    const char *hex = "0123456789ABCDEF";
    uint8_t bytes[8];
    uint8_t expected[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    
    int result = hex_to_bytes(hex, bytes, 8);
    
    assert(result == 0);
    assert(memcmp(bytes, expected, 8) == 0);
    
    printf("✓ Hex conversion tests passed\n");
}

int main() {
    printf("========================================\n");
    printf("Utility Functions Test Suite\n");
    printf("========================================\n");
    
    test_get_set_bit();
    test_xor_bytes();
    test_hex_conversion();
    
    printf("\n========================================\n");
    printf("All utility tests passed!\n");
    printf("========================================\n");
    
    return 0;
}
