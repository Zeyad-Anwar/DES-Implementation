# DES Implementation Documentation

## Overview

This document provides implementation notes and algorithm details for the DES (Data Encryption Standard) implementation.

## DES Algorithm Steps

### Encryption Process

1. **Initial Permutation (IP)**: Rearrange the 64-bit plaintext block
2. **16 Rounds of Feistel Structure**:
   - Split the block into left (L) and right (R) halves (32 bits each)
   - For each round i (1 to 16):
     - Expand R from 32 to 48 bits using E table
     - XOR with round key Ki
     - Split into 8 6-bit blocks
     - Pass through S-boxes to get 8 4-bit outputs (32 bits total)
     - Permute using P table
     - XOR with L
     - Swap: new L = old R, new R = result of XOR
3. **Final Permutation (FP)**: Inverse of initial permutation

### Decryption Process

Same as encryption, but use round keys in reverse order (K16, K15, ..., K1)

### Key Schedule

1. **PC1 Permutation**: Reduce 64-bit key to 56 bits (removes parity bits)
2. **Split**: Divide into left (C0) and right (D0) halves (28 bits each)
3. **Generate 16 Round Keys**:
   - For each round i:
     - Left shift Ci-1 and Di-1 by 1 or 2 positions (according to shift schedule)
     - Combine and apply PC2 to get 48-bit round key Ki

## S-Boxes

Each S-box maps 6 input bits to 4 output bits:

- Outer 2 bits (first and last) select the row (0-3)
- Inner 4 bits select the column (0-15)

## Testing

The implementation includes test vectors from NIST and other standards to verify correctness.

## Implementation Notes

- All operations are performed using bitwise operations
- No external cryptographic libraries are used
- The implementation follows the original DES specification (FIPS 46-3)

## Security Note

DES is considered cryptographically weak by modern standards due to its short key length (56 bits). This implementation is for educational purposes only and should not be used for securing sensitive data in production systems. Use AES or other modern encryption algorithms instead.
