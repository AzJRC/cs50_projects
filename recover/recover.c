#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

void create_img(FILE *file, char *img_address, int img_num, size_t image_length) {
    // Create the JPEG file
    char filename[12];
    snprintf(filename, sizeof(filename), "img_%03i.jpg", img_num);
    FILE *jpeg_file = fopen(filename, "wb");
    if (jpeg_file == NULL) {
        printf("Failed to create the JPEG file.\n");
        return;
    }

    int write_length = fwrite(img_address, sizeof(BYTE), image_length, jpeg_file);
    if (write_length != image_length) {
        printf("Error: Image has not been properly created.\n");
    }
    fclose(jpeg_file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Incorrect usage. Try ./recover IMAGE_FILE\n");
        return 1;
    }

    // Store image file
    char *imgfile = argv[1];
    FILE *imgfile_ptr = fopen(imgfile, "rb");

    if (imgfile_ptr == NULL) {
        printf("Can't read the file.\n");
        return 1;
    }

    // Get the length of the file
    fseek(imgfile_ptr, 0, SEEK_END);
    long img_length = ftell(imgfile_ptr);
    fseek(imgfile_ptr, 0, SEEK_SET);

    // Read the image file into memory
    BYTE *file_buffer = malloc(sizeof(BYTE) * img_length);
    if (file_buffer == NULL) {
        printf("Failed to allocate memory for file_buffer.\n");
        fclose(imgfile_ptr);
        return 1;
    }

    size_t bytes_read = fread(file_buffer, sizeof(BYTE), img_length, imgfile_ptr);
    fclose(imgfile_ptr);

    if (bytes_read != img_length) {
        printf("Error reading the file.\n");
        free(file_buffer);
        return 1;
    }

    // Search for JPEG signatures
    BYTE signature[] = {0xff, 0xd8, 0xff};
    int signature_length = sizeof(signature) / sizeof(BYTE);
    int img_finder = 0;
    int img_num = 0;

    for (size_t i = 0; i < img_length - signature_length; i++) {
        if (memcmp(&file_buffer[i], signature, signature_length) == 0 && (file_buffer[i + 3] & 0xf0) == 0xe0) {
            if (img_finder > 0) {
                // Found a new image, create the previous one
                size_t image_length = i - img_finder;
                img_num++;
                create_img(imgfile_ptr, (char *)&file_buffer[img_finder], img_num, image_length);
            }
            img_finder = i;
        }
    }

    // Create the last image
    size_t image_length = img_length - img_finder;
    img_num++;
    create_img(imgfile_ptr, (char *)&file_buffer[img_finder], img_num, image_length);

    free(file_buffer);
    printf("Total probable images: %i\n", img_num);

    return 0;
}