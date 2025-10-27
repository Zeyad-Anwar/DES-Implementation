#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

/**
 * Performs bit permutation on 64-bit data
 * @param input: Input 64-bit value
 * @param table: Permutation table (1-based indexing)
 * @param output_len: Number of output bits (e.g., 64, 56, 48, 32)
 * @return: Permuted value (aligned to MSB)
 */
uint64_t permute(uint64_t input, const uint8_t *table, int output_len);

/**
 * Gets a specific bit from a 64-bit value
 * @param data: 64-bit value
 * @param bit_pos: Bit position (0-63, where 0 is MSB)
 * @return: Bit value (0 or 1)
 */
uint8_t get_bit64(uint64_t data, int bit_pos);

/**
 * Prints a 64-bit value in hexadecimal format
 * @param data: 64-bit value
 */
void print_hex64(uint64_t data);

/**
 * Converts a hex string to 64-bit value
 * @param hex_str: Hexadecimal string (16 characters)
 * @param value: Output 64-bit value
 * @return: 0 on success, -1 on error
 */
int hex_to_uint64(const char *hex_str, uint64_t *value);

#endif /* UTILS_H */
