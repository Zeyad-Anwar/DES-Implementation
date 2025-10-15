#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void permute(const uint8_t *input, uint8_t *output, const uint8_t *table, 
             int input_len, int output_len) {
    // TODO: Implement permutation
    // For each position in output, get the bit from input at table[position]
}

uint8_t get_bit(const uint8_t *data, int bit_pos) {
    int byte_index = bit_pos / 8;
    int bit_index = 7 - (bit_pos % 8);
    return (data[byte_index] >> bit_index) & 0x01;
}

void set_bit(uint8_t *data, int bit_pos, uint8_t value) {
    int byte_index = bit_pos / 8;
    int bit_index = 7 - (bit_pos % 8);
    if (value) {
        data[byte_index] |= (1 << bit_index);
    } else {
        data[byte_index] &= ~(1 << bit_index);
    }
}

void xor_bytes(const uint8_t *a, const uint8_t *b, uint8_t *result, int len) {
    for (int i = 0; i < len; i++) {
        result[i] = a[i] ^ b[i];
    }
}

void print_hex(const uint8_t *data, int len) {
    for (int i = 0; i < len; i++) {
        printf("%02X", data[i]);
    }
    printf("\n");
}

int hex_to_bytes(const char *hex_str, uint8_t *bytes, int len) {
    if (strlen(hex_str) != (size_t)(len * 2)) {
        return -1;
    }
    
    for (int i = 0; i < len; i++) {
        char byte_str[3] = {hex_str[i*2], hex_str[i*2+1], '\0'};
        if (!isxdigit(byte_str[0]) || !isxdigit(byte_str[1])) {
            return -1;
        }
        sscanf(byte_str, "%2hhx", &bytes[i]);
    }
    
    return 0;
}
