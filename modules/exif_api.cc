#include<stdlib.h>
#include<stdio.h>
#include <exif.h>

#include <iostream>
#include <exif_api.h>

#include <json.hpp>


using json = nlohmann::json;
using namespace easyexif;

easyexif::EXIFInfo get_exif_data(unsigned char * jpegBuffer, unsigned long * size, int *r_code) {
    if(* size <= 0  || !jpegBuffer) {
        printf("invalid data supplied");
        exit(0);
    }

    easyexif::EXIFInfo result;
    int code = result.parseFrom(jpegBuffer, *size);
    *r_code = code; 
    if(code) {
        printf("EXIF data cant be read!");
    }
    return result;
}

void exif_to_print(easyexif::EXIFInfo result) {
  printf("Camera make          : %s\n", result.Make.c_str());
  printf("Camera model         : %s\n", result.Model.c_str());
  printf("Software             : %s\n", result.Software.c_str());
  printf("Bits per sample      : %d\n", result.BitsPerSample);
  printf("Image width          : %d\n", result.ImageWidth);
  printf("Image height         : %d\n", result.ImageHeight);
  printf("Image description    : %s\n", result.ImageDescription.c_str());
  printf("Image orientation    : %d\n", result.Orientation);
  printf("Image copyright      : %s\n", result.Copyright.c_str());
  printf("Image date/time      : %s\n", result.DateTime.c_str());
  printf("Original date/time   : %s\n", result.DateTimeOriginal.c_str());
  printf("Digitize date/time   : %s\n", result.DateTimeDigitized.c_str());
  printf("Subsecond time       : %s\n", result.SubSecTimeOriginal.c_str());
  printf("Exposure time        : 1/%d s\n",
         (unsigned)(1.0 / result.ExposureTime));
  printf("F-stop               : f/%.1f\n", result.FNumber);
  printf("Exposure program     : %d\n", result.ExposureProgram);
  printf("ISO speed            : %d\n", result.ISOSpeedRatings);
  printf("Subject distance     : %f m\n", result.SubjectDistance);
  printf("Exposure bias        : %f EV\n", result.ExposureBiasValue);
  printf("Flash used?          : %d\n", result.Flash);
  printf("Flash returned light : %d\n", result.FlashReturnedLight);
  printf("Flash mode           : %d\n", result.FlashMode);
  printf("Metering mode        : %d\n", result.MeteringMode);
  printf("Lens focal length    : %f mm\n", result.FocalLength);
  printf("35mm focal length    : %u mm\n", result.FocalLengthIn35mm);
  printf("GPS Latitude         : %f deg (%f deg, %f min, %f sec %c)\n",
         result.GeoLocation.Latitude, result.GeoLocation.LatComponents.degrees,
         result.GeoLocation.LatComponents.minutes,
         result.GeoLocation.LatComponents.seconds,
         result.GeoLocation.LatComponents.direction);
  printf("GPS Longitude        : %f deg (%f deg, %f min, %f sec %c)\n",
         result.GeoLocation.Longitude, result.GeoLocation.LonComponents.degrees,
         result.GeoLocation.LonComponents.minutes,
         result.GeoLocation.LonComponents.seconds,
         result.GeoLocation.LonComponents.direction);
  printf("GPS Altitude         : %f m\n", result.GeoLocation.Altitude);
  printf("GPS Precision (DOP)  : %f\n", result.GeoLocation.DOP);
  printf("Lens min focal length: %f mm\n", result.LensInfo.FocalLengthMin);
  printf("Lens max focal length: %f mm\n", result.LensInfo.FocalLengthMax);
  printf("Lens f-stop min      : f/%.1f\n", result.LensInfo.FStopMin);
  printf("Lens f-stop max      : f/%.1f\n", result.LensInfo.FStopMax);
  printf("Lens make            : %s\n", result.LensInfo.Make.c_str());
  printf("Lens model           : %s\n", result.LensInfo.Model.c_str());
  printf("Focal plane XRes     : %f\n", result.LensInfo.FocalPlaneXResolution);
  printf("Focal plane YRes     : %f\n", result.LensInfo.FocalPlaneYResolution);
}

std::string exif_to_json(easyexif::EXIFInfo result) {
    json json_d;

    json_d["camera_make"] = result.Make.c_str();
    json_d["camera_model"] = result.Model.c_str();
    json_d["software"] = result.Software.c_str();
    json_d["bits_per_sample"] = result.BitsPerSample;
    json_d["image_width"] = result.ImageWidth;
    json_d["image_height"] = result.ImageHeight;
    json_d["image_description"] = result.ImageDescription.c_str();
    json_d["image_orientation"] = result.Orientation;
    json_d["image_copyright"] = result.Copyright.c_str();
    json_d["image_date_time"] = result.DateTime.c_str();
    json_d["image_original_date_time"] = result.DateTimeOriginal.c_str();
    json_d["image_digitized_date_time"] = result.DateTimeDigitized.c_str();
    json_d["subsecond_time"] = result.SubSecTimeOriginal.c_str();
    json_d["exposure_time"] = (unsigned)(1.0 / result.ExposureTime);
    json_d["f_stop"] =result.FNumber;
    json_d["exposure_program"]=result.ExposureProgram;
    json_d["iso_speed"] = result.ISOSpeedRatings;
    json_d["subject_distance"] = result.SubjectDistance;
    json_d["expousre_bias"] = result.ExposureBiasValue;
    json_d["flash_used"] = result.Flash;
    json_d["flash_returned_light"]=result.FlashReturnedLight;

    json_d["flash_mode"]=result.MeteringMode;
    json_d["metering_mode"]=result.FocalLength;
    json_d["lens_focal_length"] =result.FocalLength;
    json_d["35m_focal_length"] = result.FocalLengthIn35mm;
    json_d["gps_alatitude"] = result.GeoLocation.Altitude;
    json_d["gps_precision"] = result.GeoLocation.DOP;
    json_d["lens_min_focal_length"] = result.LensInfo.FocalLengthMin;
    json_d["lens_max_focal_length"] = result.LensInfo.FocalLengthMax;
    json_d["lens_f_stop_min"] = result.LensInfo.FStopMin;
    json_d["lens_f_stop_max"] = result.LensInfo.FStopMax;
    json_d["lens_make"] = result.LensInfo.Make.c_str();
    json_d["lens_model"] = result.LensInfo.Model.c_str();
    json_d["focal_plane_xres"] = result.LensInfo.FocalPlaneXResolution;
    json_d["focal_plane_yres"] = result.LensInfo.FocalPlaneYResolution;

    //GPU coords
    json_d["location"]["lat"]["lat"] = result.GeoLocation.Latitude;
    json_d["location"]["lat"]["degree"] = result.GeoLocation.LatComponents.degrees;
    json_d["location"]["lat"]["minutes"] = result.GeoLocation.LatComponents.minutes;
    json_d["location"]["lat"]["seconds"] = result.GeoLocation.LatComponents.seconds;
    json_d["location"]["lat"]["direction"] = result.GeoLocation.LatComponents.direction;

    json_d["location"]["lon"]["lon"] = result.GeoLocation.Longitude;
    json_d["location"]["lon"]["degree"] = result.GeoLocation.LonComponents.degrees;
    json_d["location"]["lon"]["minutes"] = result.GeoLocation.LonComponents.minutes;
    json_d["location"]["lon"]["seconds"] = result.GeoLocation.LonComponents.seconds;
    json_d["location"]["lon"]["direction"] = result.GeoLocation.LonComponents.direction;

    std::string jsonString = json_d.dump();
    return jsonString;
}
