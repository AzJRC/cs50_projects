#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>

#define AES_BLOCK_SIZE 16

void encrypt(const unsigned char *plaintext, int plaintext_len, const unsigned char *key, unsigned char *ciphertext) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);
    AES_encrypt(plaintext, ciphertext, &aes_key);
}

void decrypt(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key, unsigned char *plaintext) {
    AES_KEY aes_key;
    AES_set_decrypt_key(key, 128, &aes_key);
    AES_decrypt(ciphertext, plaintext, &aes_key);
}

    algorithm(const unsigned char *plaintext, int block_size, const unsigned char *key, const int block_number) {
    unsigned char ciphertext[block_size];
    unsigned char decrypted_text[block_size];

    // Encryption
    encrypt(plaintext, block_size, key, ciphertext);
    printf("Ciphertext: ");
    for (int i = 0; i < block_size; ++i)
        printf("%02x", ciphertext[i]);
    printf("\n");

    // Decryption
    decrypt(ciphertext, block_size, key, decrypted_text);
    printf("Decrypted text: ");
    for(int i = 0; i < 16; i++) {
        printf("%c", decrypted_text[i]);
    }
    printf("\n");
}

int main() {
    const unsigned char key[AES_BLOCK_SIZE] = "0123456789abcdef";
    const unsigned char plaintext[] = "abcdefghijklmnopqrstuvwxyz";
    const int block_size = 16;
    
    int num_blocks = strlen(plaintext) / block_size;
    if (strlen(plaintext) % block_size != 0)
        num_blocks++;

    // Divide plaintext into byte blocks
    unsigned char *buffer = malloc(block_size);
    for (int block_number = 0; block_number < num_blocks; block_number++) {
        int start_index = block_number * block_size;
        int end_index = start_index + block_size;
        
        memset(buffer, 0, block_size);
        memcpy(buffer, &plaintext[start_index], end_index - start_index);
        
        algorithm(buffer, block_size, key, block_number);
    }

    free(buffer);

    return 0;
}