#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "des.h"
#include "utils.h"


// test libraries
#include <inttypes.h>


// Global variables
char *key_filename = NULL; // Global variable to hold the key filename
char *plaintext_filename = NULL; // Global variable to hold the plaintext filename
char *ciphertext_filename = NULL; // Global variable to hold the ciphertext filename


// function prototypes
uint64_t get_key(const char *key_filename);
size_t get_file_size(const char *filename);
void encrypt_file(const char *key_filename, const char *plaintext_filename, const char *ciphertext_filename);
void decrypt_file(const char *key_filename, const char *ciphertext_filename, const char *plaintext_filename);

int main(int argc, char *argv[]) {

    // check for the mode (encryption or decryption)
    if(strcmp(argv[1],"e") == 0){ // then encrypt the text
        key_filename = argv[2];
        plaintext_filename = argv[3];
        ciphertext_filename = argv[4];

        encrypt_file(key_filename, plaintext_filename, ciphertext_filename);
    }
    else{ // then decrypt the text
        key_filename = argv[2];
        ciphertext_filename = argv[3];
        plaintext_filename = argv[4];

        decrypt_file(key_filename, ciphertext_filename, plaintext_filename);
    }
    
    return 0;
}


// function definitions
uint64_t get_key(const char *key_filename) {
    // read the key from the key file
    FILE *keyfileptr = fopen(key_filename, "rb");

    uint64_t key;
    fread(&key, sizeof(key), 1, keyfileptr);

    printf("\n the value of key is 0x%016" PRIx64 "\n", key);
    return key;
}

size_t get_file_size(const char *filename) {
    // get the size of the file
    struct stat st;
    stat(filename, &st);

    size_t filesize = st.st_size;
    return filesize;
}

void encrypt_file(const char *key_filename, const char *plaintext_filename, const char *ciphertext_filename) {
    // Function to encrypt the file
    uint64_t key = get_key(key_filename);

    // read the plaintext from the plaintext file
    FILE *plaintextfileptr = fopen(plaintext_filename, "rb");

    // get the size of the file
    size_t filesize = get_file_size(plaintext_filename);
    printf("\n the size of the plaintext file is %zu bytes\n", filesize);

    // make an array to hold the plaintext
    size_t num_blocks = filesize / 8;
    uint64_t *plaintext = (uint64_t *)malloc(filesize);
    uint64_t *ciphertext = (uint64_t *)malloc(filesize);

    // read the plaintext into the array
    fread(plaintext, sizeof(uint64_t), num_blocks, plaintextfileptr);
    fclose(plaintextfileptr);
    
    // encrypt all blocks (loop is inside des_encrypt)
    des_encrypt(plaintext, key, ciphertext, num_blocks);

    // write the ciphertext to the ciphertext file
    FILE *ciphertextfileptr = fopen(ciphertext_filename, "wb+");
    fwrite(ciphertext, sizeof(uint64_t), num_blocks, ciphertextfileptr);
    fclose(ciphertextfileptr);
    
    free(plaintext);
    free(ciphertext);
}

void decrypt_file(const char *key_filename, const char *ciphertext_filename, const char *plaintext_filename) {
    // Function to decrypt the file
    uint64_t key = get_key(key_filename);
    
    // read the ciphertext from the ciphertext file
    FILE *ciphertextfileptr = fopen(ciphertext_filename, "rb");

    // get the size of the file
    size_t filesize = get_file_size(ciphertext_filename);
    printf("\n the size of the ciphertext file is %zu bytes\n", filesize);

    // make an array to hold the ciphertext
    size_t num_blocks = filesize / 8;
    uint64_t *ciphertext = (uint64_t *)malloc(filesize);
    uint64_t *plaintext = (uint64_t *)malloc(filesize);
    
    // read the ciphertext into the array
    fread(ciphertext, sizeof(uint64_t), num_blocks, ciphertextfileptr);
    fclose(ciphertextfileptr);
    
    // decrypt all blocks (loop is inside des_decrypt)
    des_decrypt(ciphertext, key, plaintext, num_blocks);

    // write the plaintext to the plaintext file
    FILE *plaintextfileptr = fopen(plaintext_filename, "wb+");
    fwrite(plaintext, sizeof(uint64_t), num_blocks, plaintextfileptr);
    fclose(plaintextfileptr);
    
    free(ciphertext);
    free(plaintext);
}