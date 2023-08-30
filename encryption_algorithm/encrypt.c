#include <stdio.h>
#include <string.h>
#include <openssl/des.h>

void encryptDES(const unsigned char *plaintext, unsigned char *ciphertext, const DES_key_schedule *key_schedule) {
    DES_ecb_encrypt(plaintext, ciphertext, key_schedule, DES_ENCRYPT);
}

void decryptDES(const unsigned char *ciphertext, unsigned char *plaintext, const DES_key_schedule *key_schedule) {
    DES_ecb_encrypt(ciphertext, plaintext, key_schedule, DES_DECRYPT);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Incorrect program use. Try ./encrypt.exe key message\n");
        return 1;
    }

    // Convert key into hexadecimal bytes
    unsigned char key[8];
    if (strlen(argv[1]) == 16) {
        for (int i = 0; i < 8; i++) {
            sscanf(argv[1] + i * 2, "%2hhx", &key[i]);
        }
    } else {
        printf("Wrong key format. Try again (The key should be 16 characters long).\n");
        return 1;
    }

    // Example plaintext (multiple of 8 bytes for simplicity)
    unsigned char *plaintext[] = getchar();
    

    // Buffer for the encrypted ciphertext
    unsigned char ciphertext[sizeof(plaintext)];

    // Buffer for the decrypted plaintext
    unsigned char decrypted[sizeof(plaintext)];

    DES_key_schedule key_schedule;
    DES_set_key((DES_cblock*)key, &key_schedule);

    // Encryption
    encryptDES(plaintext, ciphertext, &key_schedule);
    printf("Encrypted: %s\n", ciphertext);

    // Decryption
    decryptDES(ciphertext, decrypted, &key_schedule);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}