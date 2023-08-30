#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define PDF_SIGNATURE "%PDF"

int main(int argc, char *argv[]) {
    //proper usage
    if (argc != 2) {
        printf("You must include only one argument (Name of the document).\n");
        return 1;
    }

    //open file
    char *filename = malloc(sizeof(char) * strlen(argv[1]) + 1);
    sprintf(filename, "%s", argv[1]);
    
    if (filename == NULL) 
    {
        printf("Error.\n");
        return 1;
    }
    FILE *pdf = fopen(filename, "r");
    
    //check file existance
    if (pdf == NULL) {
        printf("File not found.\n");
        return 1;
    }

    //reading the file
    uint8_t buff[4];
    fread(buff, 1, 4, pdf);
    fclose(pdf);
    
    //result
    for (int i = 0; i < 4; i++) {
        if (buff[i] != PDF_SIGNATURE[i]) {
            printf("Likely not a PDF file.");
            return 0;
        }
    }
    printf("Likely a PDF file.\n");
    return 0;
}