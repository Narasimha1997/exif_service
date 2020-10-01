#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <httplib.h>
#include <exif_api.h>


unsigned char * make_image_buffer(int size) {
    return (unsigned char *)malloc(size);
}

void create_server_object() {
    httplib::Server server;

    server.Post("/jpeg", [&](const auto& req, auto& res) {
        auto ret = req.has_file("image");
        const auto& file = req.get_file_value("image");

        unsigned long size = file.content.length();
        
        unsigned char * buffer = make_image_buffer(size);

        memcpy(buffer, file.content.c_str(), size);

        int r_code = 0;

        easyexif::EXIFInfo result = get_exif_data(buffer, &size, &r_code);

        if(buffer) {
            memset(buffer, 0, sizeof(*buffer));
            free(buffer);
        }

        if(r_code) {
            res.set_content("Image file cant be read, upload valid JPEG, or no exif data found", "text/plain");
        }

        //exif_to_print(result);
        std::string jsonData = exif_to_json(result);
        res.set_content(jsonData.c_str(), "application/json");
    });


    server.Get("/health", [&](const auto& req, auto& res) {
        std::cout<<"Health Endpoint got hit"<<std::endl;
        res.set_content("Active", "text/plain");
    });

   std::cout<<"Listening on http://0.0.0.0:8888"<<std::endl;

    server.listen("0.0.0.0", 8888);
}

