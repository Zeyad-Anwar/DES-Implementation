#ifndef TEST_VECTORS_H
#define TEST_VECTORS_H

#include <stdint.h>


typedef struct {
    const char *name;
    uint64_t plaintext;
    uint64_t key;
    uint64_t expected_ciphertext;
} test_vector_t;

static const test_vector_t test_vectors[] = {
    {
        "NIST Test Vector 1",
        0x0123456789ABCDEFULL,
        0x133457799BBCDFF1ULL,
        0x85E813540F0AB405ULL
    },
    {
        "All zeros",
        0x0000000000000000ULL,
        0x0000000000000000ULL,
        0x8CA64DE9C1B123A7ULL
    },
    {
        "All ones",
        0xFFFFFFFFFFFFFFFFULL,
        0xFFFFFFFFFFFFFFFFULL,
        0x7359B2163E4EDC58ULL
    },
    {
        "Weak key test",
        0x95F8A5E5DD31D900ULL,
        0x0101010101010101ULL,
        0x8000000000000000ULL
    }
};

#define NUM_TEST_VECTORS (sizeof(test_vectors) / sizeof(test_vectors[0]))

#endif /* TEST_VECTORS_H */
