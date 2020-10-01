#ifndef __IMAGE_READER_H

#define __IMAGE_READER_H

unsigned char * create_jpeg_buffer(unsigned long size);
unsigned char * read_jpeg_data_fs(char * path, unsigned long * size);

#endif