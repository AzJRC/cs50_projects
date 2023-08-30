#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <openssl/aes.h>

#define BLOCK_SIZE 16
#define MAX_INPUT 1024

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

int main() {
    // 2 Byte key
    printf("Enter a key: ");
    unsigned char key[BLOCK_SIZE];
    scanf("%s", key);

    // Plaintext to be encrypted
    printf("Enter the plaintext: ");
    char plaintext[MAX_INPUT];
    scanf(" %[^\n]s", plaintext); // Read the entire line, including whitespaces

    //divide plaintext into two-byte blocks
    const int plaintext_length = strlen(plaintext);
    float num_byte_blocks = (plaintext_length/(float) BLOCK_SIZE);
    //printf("Num of blocks is: %i\n", (int) ceil(num_byte_blocks));
    unsigned char *text_to_encrypt = malloc(sizeof(num_byte_blocks * BLOCK_SIZE)); //Here we will store the text to encrypt
    strcpy(text_to_encrypt, plaintext);
    int padding_required = 0;
    
    //determine and set padding of last block if required
    if (ceil(num_byte_blocks - ceil(num_byte_blocks) != 0)) {
        padding_required = ceil(num_byte_blocks) * BLOCK_SIZE - plaintext_length;
        //printf("Last block requires %i characters of padding.\n", padding_required);
        for (int i = 0; i < padding_required; i++) {
            //printf("Padding %i added.\n", i + 1);
            text_to_encrypt[plaintext_length + i] = ' ';
        }
    }

    // encrypt and decrypt block by block
    int show_print_messages = 1;
    for (int block_number = 0; block_number < num_byte_blocks; block_number++) {
        int block_start_index = block_number * BLOCK_SIZE;
        int block_end_index = block_start_index + BLOCK_SIZE;
        char *buffer = malloc(BLOCK_SIZE + 1);

        memset(buffer, 0, BLOCK_SIZE);
        memcpy(buffer, &text_to_encrypt[block_start_index], block_end_index - block_start_index);
        buffer[BLOCK_SIZE] = '\0';

        //encrypt buffer
        unsigned char ciphertext[BLOCK_SIZE];
        unsigned char decrypted_text[BLOCK_SIZE];

        encrypt(buffer, BLOCK_SIZE, key, ciphertext);
        if (show_print_messages) {
            printf("Ciphertext: ");
            for (int i = 0; i < BLOCK_SIZE; ++i)
                printf("%02x", ciphertext[i]);
            printf("\n");
        }

        //decrypt buffer
        decrypt(ciphertext, BLOCK_SIZE, key, decrypted_text);
        if (show_print_messages) {
            printf("Decrypted text: ");
            show_print_messages--; //show ciphertext just one time
        }
        for(int i = 0; i < 16; i++) {
            printf("%c", decrypted_text[i]);
        }
    }
    return 0;
}