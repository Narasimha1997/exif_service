#include <exif_api.h>
#include <httplib.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utils.h>

unsigned char* make_image_buffer(int size)
{
    return (unsigned char*)malloc(size);
}

void create_server_object(JsonLogger *logging)
{
    httplib::Server server;

    server.Post("/jpeg", [&](const auto& req, auto& res) {

        logging->logInfo("Server got request");

        auto ret = req.has_file("image");
        if (!ret) {

            logging->logError("No attribute image present in the request");

            std::string fail_data = get_fail_data("No attribute image present in the request");

            res.set_content(
                fail_data, 
                "application/json"
            );

            return;
        } 

        const auto& file = req.get_file_value("image");

        unsigned long size = file.content.length();

        unsigned char* buffer = make_image_buffer(size);

        memcpy(buffer, file.content.c_str(), size);

        int r_code = 0;

        easyexif::EXIFInfo result = get_exif_data(buffer, &size, &r_code);

        if (r_code) {

            logging->logError("Image file cant be read, upload valid JPEG, or no exif data found");
            
            std::string fail_data = get_fail_data("Image file cant be read, upload valid JPEG, or no exif data found");
            res.set_content(
                fail_data,
                "application/json"
            );
            return;
        }

        //exif_to_print(result);
        logging->logInfo("Successfully processed request");

        std::string jsonData = exif_to_json(result);
        res.set_content(jsonData.c_str(), "application/json");
    });

    server.Get("/health", [&](const auto& req, auto& res) {
        logging->logInfo("Health Endpoint got hit");
        std::string message = get_health_response();
        res.set_content(message.c_str(), "application/json");
    });

    std::cout << "Listening on http://0.0.0.0:8888" << std::endl;

    server.listen("0.0.0.0", 8888);
}
