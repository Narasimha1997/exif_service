# exif_service
A C++ microservice used to extract location and other forensic information from JPEG images.

### How to run 
The application needs to be compiled and linked to generate a binary for target platform. It can be run on host machine as well as in a container.

#### Run on host machine :
Any x86 Linux host can easily run this binary. Follow the instructions below :
`GNU G++` and `make` are enough to build this on any linux distro. 

1. Generate the binary :
We have provided a makefile to ease build process. 
```
make web
```
This will generate the binary at `build/server`

2. Run the binary :
We can run the binary using following command :
```
$./build/server
Listening on http://0.0.0.0:8888

```
This will run the server. 

#### Build a docker image :
To reduce the size of docker image, we have used alpine-linux as base with minimal required dependencies.

1. Build the docker :
Build the image using command below :
```
docker build . -t exif_service
```

2. Spin up the container :
```
docker run --rm -ti --net=host exif_service
```

### Using the REST Api:
The server provides two rest endpoints :
1. Check health of the service :
This endpoint is just like ping.
```
curl http://localhost:8888/health
```

2. Run exif extraction:
The endpoint `jpeg` takes `multipart/form-data` and produces JSON output.
```
curl -X POST -F 'image=@{IMAGE_ABS_PATH}/image.jpg' -H Content-Type:multipart/form-data" http://localhost:8888/jpeg | json_pp
```

The output is a list of complete image information as per EXIF standard.

```json
{
   "focal_plane_xres" : 0,
   "35m_focal_length" : 0,
   "image_original_date_time" : "",
   "image_width" : 0,
   "expousre_bias" : 0,
   "image_digitized_date_time" : "",
   "exposure_time" : 0,
   "f_stop" : 0,
   "software" : "",
   "subject_distance" : 0,
   "iso_speed" : 0,
   "lens_f_stop_min" : 0,
   "bits_per_sample" : 0,
   "image_date_time" : "",
   "metering_mode" : 0,
   "flash_mode" : 0,
   "gps_precision" : 0,
   "gps_alatitude" : 0,
   "subsecond_time" : "",
   "lens_f_stop_max" : 0,
   "flash_returned_light" : 0,
   "image_orientation" : 0,
   "exposure_program" : 0,
   "location" : {
      "lat" : {
         "minutes" : 0,
         "degree" : 0,
         "direction" : 63,
         "seconds" : 0,
         "lat" : 0
      },
      "lon" : {
         "degree" : 0,
         "minutes" : 0,
         "direction" : 63,
         "lon" : 0,
         "seconds" : 0
      }
   },
   "camera_make" : "",
   "lens_min_focal_length" : 0,
   "focal_plane_yres" : 0,
   "image_copyright" : "",
   "lens_make" : "",
   "camera_model" : "",
   "image_description" : "",
   "lens_focal_length" : 0,
   "lens_max_focal_length" : 0,
   "lens_model" : "",
   "image_height" : 0,
   "flash_used" : 0
}
```
The values are purposefully emptied/zeroed to protect sensitive information.

### Acknowledgements :
1. [EasyEXIF](https://github.com/mayanklahiri/easyexif)
2. [cpp-httplib](https://github.com/yhirose/cpp-httplib)
3. [json](https://github.com/nlohmann/json)
