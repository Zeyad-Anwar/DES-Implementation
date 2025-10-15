#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

/**
 * Performs a permutation on input bits according to a permutation table
 * @param input: Input bits
 * @param output: Output bits after permutation
 * @param table: Permutation table
 * @param input_len: Number of input bits
 * @param output_len: Number of output bits
 */
void permute(const uint8_t *input, uint8_t *output, const uint8_t *table, 
             int input_len, int output_len);

/**
 * Gets a specific bit from a byte array
 * @param data: Byte array
 * @param bit_pos: Bit position (0-indexed)
 * @return: Bit value (0 or 1)
 */
uint8_t get_bit(const uint8_t *data, int bit_pos);

/**
 * Sets a specific bit in a byte array
 * @param data: Byte array
 * @param bit_pos: Bit position (0-indexed)
 * @param value: Bit value (0 or 1)
 */
void set_bit(uint8_t *data, int bit_pos, uint8_t value);

/**
 * Performs XOR operation on two byte arrays
 * @param a: First input
 * @param b: Second input
 * @param result: XOR result
 * @param len: Length in bytes
 */
void xor_bytes(const uint8_t *a, const uint8_t *b, uint8_t *result, int len);

/**
 * Prints a byte array in hexadecimal format
 * @param data: Byte array
 * @param len: Length in bytes
 */
void print_hex(const uint8_t *data, int len);

/**
 * Converts a hex string to byte array
 * @param hex_str: Hexadecimal string
 * @param bytes: Output byte array
 * @param len: Expected length in bytes
 * @return: 0 on success, -1 on error
 */
int hex_to_bytes(const char *hex_str, uint8_t *bytes, int len);

#endif /* UTILS_H */
