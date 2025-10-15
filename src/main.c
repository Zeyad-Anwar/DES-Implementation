#include <stdio.h>
#include <string.h>
#include "des.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    printf("DES Encryption/Decryption Implementation\n");
    printf("=========================================\n\n");
    
    // Example usage
    uint8_t plaintext[DES_BLOCK_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    uint8_t key[DES_KEY_SIZE] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};
    uint8_t ciphertext[DES_BLOCK_SIZE];
    uint8_t decrypted[DES_BLOCK_SIZE];
    
    printf("Plaintext:  ");
    print_hex(plaintext, DES_BLOCK_SIZE);
    
    printf("Key:        ");
    print_hex(key, DES_KEY_SIZE);
    
    // Encrypt
    des_encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: ");
    print_hex(ciphertext, DES_BLOCK_SIZE);
    
    // Decrypt
    des_decrypt(ciphertext, key, decrypted);
    printf("Decrypted:  ");
    print_hex(decrypted, DES_BLOCK_SIZE);
    
    // Verify
    if (memcmp(plaintext, decrypted, DES_BLOCK_SIZE) == 0) {
        printf("\n✓ Encryption/Decryption successful!\n");
    } else {
        printf("\n✗ Encryption/Decryption failed!\n");
    }
    
    return 0;
}
