#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

uint64_t permute(uint64_t input, const uint8_t *table, int output_len) {
    uint64_t output = 0;
    
    // For each bit position in the output
    for (int i = 0; i < output_len; i++) {        
        // Extract the bit from the input at the source position
        // Bit 0 is the MSB (leftmost bit)
        uint64_t bit_value = (input >> (table[i])) & 1ULL;
        
        // Place the bit in the output at position i (from MSB)
        output |= (bit_value << (63 - i));
    }
    
    return output;
}

uint8_t get_bit64(uint64_t data, int bit_pos) {
    // Bit 0 is MSB, bit 63 is LSB
    return (data >> (63 - bit_pos)) & 1ULL;
}

void print_hex64(uint64_t data) {
    printf("%016lX\n", data);
}

int hex_to_uint64(const char *hex_str, uint64_t *value) {
    if (strlen(hex_str) != 16) {
        return -1;
    }
    
    *value = 0;
    for (int i = 0; i < 16; i++) {
        if (!isxdigit(hex_str[i])) {
            return -1;
        }
        
        char c = hex_str[i];
        uint64_t digit;
        
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'a' && c <= 'f') {
            digit = c - 'a' + 10;
        } else if (c >= 'A' && c <= 'F') {
            digit = c - 'A' + 10;
        } else {
            return -1;
        }
        
        *value = (*value << 4) | digit;
    }
    
    return 0;
}
