
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <exif_api.h>
#include <image_reader.h>

void dump_json(const char * jsonString) {

    FILE * writer = fopen("result.json", "w");
    if(!writer) {
        printf("Unable to write result!");
        exit(0);
    }

    fprintf(writer, "%s", jsonString);
    fclose(writer);
}

int main(int argc, char **argv) {
    if(argc == 1) {
        printf("Too few arguments.");
        exit(0);
    }
    unsigned long size = 0;
    int r_code = 0;
    unsigned char * imageBuffer = read_jpeg_data_fs(argv[1], &size);

    easyexif::EXIFInfo result = get_exif_data(imageBuffer, &size, &r_code);
    if(r_code) {
        exit(0);
    }

    free(imageBuffer);

    exif_to_print(result);
    //delete &result;
    if (argc == 2) {
        if(strcmp(argv[1], "json") == 0) {
            std::string jsonData = exif_to_json(result);
            dump_json(jsonData.c_str());
        } else {
            printf("Invalid output file format %s\n", argv[1]);
        }
    }

    return 0;
}