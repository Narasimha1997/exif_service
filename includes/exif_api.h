#ifndef __EXIF_API_H

#define __EXIF_API_H

#include <iostream>
#include <exif.h>

easyexif::EXIFInfo get_exif_data(unsigned char * jpegBuffer, unsigned long * size, int *r_code);
void exif_to_print(easyexif::EXIFInfo result);
std::string exif_to_json(easyexif::EXIFInfo result);

#endif