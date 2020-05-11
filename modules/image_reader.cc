#include <stdio.h>
#include <stdlib.h>

unsigned char * create_jpeg_buffer(unsigned long size) {
    unsigned char * buffer = (unsigned char *)malloc(size);
    return buffer;
}

#include <image_reader.h>

unsigned char * read_jpeg_data_fs(char * path, unsigned long * size) {
    FILE * jpegFp = fopen(path, "rb");
    if(! jpegFp) {
        printf("Invalid file path %s\n", path);
        exit(0);
    }

    fseek(jpegFp, 0, SEEK_END);
    * size = ftell(jpegFp);
    rewind(jpegFp);

    unsigned char * buffer = create_jpeg_buffer(*size);
    if (fread(buffer, 1, *size, jpegFp) != *size) {
        printf("Can't read file.\n");
        exit(0);
    }

    fclose(jpegFp);

    return buffer;
}