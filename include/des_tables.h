#ifndef DES_TABLES_H
#define DES_TABLES_H

#include <stdint.h>

/* Initial Permutation (IP) table */
extern const uint8_t IP[64];

/* Final Permutation (FP) table */
extern const uint8_t FP[64];

/* Expansion (E) table */
extern const uint8_t E[48];

/* Permutation (P) table */
extern const uint8_t P[32];

/* Permuted Choice 1 (PC1) table */
extern const uint8_t PC1[56];

/* Permuted Choice 2 (PC2) table */
extern const uint8_t PC2[48];

/* Left shift schedule for key generation */
extern const uint8_t LEFT_SHIFTS[16];

/* S-boxes (8 boxes, each 4x16) */
extern const uint8_t S[8][4][16];

#endif /* DES_TABLES_H */
