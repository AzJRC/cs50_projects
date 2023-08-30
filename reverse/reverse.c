#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(const WAVHEADER *header);
int get_block_size(const WAVHEADER *header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3) {
        printf("Usage: ./reverse.exe input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    const char *filename = argv[1];
    FILE *audio_file = fopen(filename, "rb");
    if (audio_file == NULL) {
        printf("Error: Unable to open input file.\n");
        return 1;
    }

    // Read header
    WAVHEADER header_buffer;
    if (fread(&header_buffer, sizeof(WAVHEADER), 1, audio_file) != 1) {
        printf("Error: Unable to read WAV file header.\n");
        fclose(audio_file);
        return 1;
    }

    // Use check_format to ensure WAV format
    if (!check_format(&header_buffer)) {
        printf("Error: Only .wav files are supported.\n");
        fclose(audio_file);
        return 1;
    }

    // Close input file
    fclose(audio_file);

    // Open output file for writing
    const char *output_filename = argv[2];
    FILE *new_audio_file = fopen(output_filename, "wb");
    if (new_audio_file == NULL) {
        printf("Error: Unable to open output file.\n");
        return 1;
    }

    // Write header to file
    fwrite(&header_buffer, sizeof(WAVHEADER), 1, new_audio_file);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(&header_buffer);

    // Open input file again for reading
    audio_file = fopen(filename, "rb");
    if (audio_file == NULL) {
        printf("Error: Unable to open input file for reading.\n");
        fclose(new_audio_file);
        return 1;
    }

    // Skip the header in the input file
    fseek(audio_file, sizeof(WAVHEADER), SEEK_SET);

    // Write reversed audio to file
    BYTE *audio_buffer = (BYTE *)malloc(block_size);
    if (audio_buffer == NULL) {
        printf("Error: Memory allocation failed.\n");
        fclose(audio_file);
        fclose(new_audio_file);
        return 1;
    }

    // Get the file size
    fseek(audio_file, 0, SEEK_END);
    long file_size = ftell(audio_file);
    fseek(audio_file, sizeof(WAVHEADER), SEEK_SET);

    // Calculate the number of blocks in the audio file
    int num_blocks = (file_size - sizeof(WAVHEADER)) / block_size;

    // Read and write each block in reverse order
    for (int i = num_blocks - 1; i >= 0; i--) {
        fseek(audio_file, i * block_size + sizeof(WAVHEADER), SEEK_SET);
        fread(audio_buffer, 1, block_size, audio_file);
        fwrite(audio_buffer, 1, block_size, new_audio_file);
    }

    // Close files and free memory
    fclose(audio_file);
    fclose(new_audio_file);
    free(audio_buffer);

    return 0;
}

int check_format(const WAVHEADER *header)
{
    const BYTE expectedFormat[] = { 'W', 'A', 'V', 'E' };
    if (memcmp(header->format, expectedFormat, sizeof(expectedFormat)) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int get_block_size(const WAVHEADER *header)
{
    int block_size = header->numChannels * (header->bitsPerSample / 8);
    return block_size;
}