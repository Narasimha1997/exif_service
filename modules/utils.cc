#include <json.hpp>
#include <utils.h>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using json = nlohmann::json;

static inline std::string getISOTime()
{
    auto now = std::chrono::system_clock::now();
    auto now_tt = std::chrono::system_clock::to_time_t(now);

    std::ostringstream string_stream;
    string_stream << std::put_time(gmtime(&now_tt), "%FT%TZ");

    std::string time = string_stream.str();
    return time;
}

std::string get_health_response()
{
    json health_json;
    health_json["status"] = true;
    health_json["state"] = "running";

    std::string data = health_json.dump();
    return data;
}

JsonLogger::JsonLogger(const char* file_name)
{
    if (!file_name) {
        fprintf(stdout, "Empty log file provided, skipping log file writing.\n");
    }

    this->fp = fopen(file_name, "a");
    if (!fp) {
        fprintf(stdout, "Failed to open file, will write to stdout.\n");
    }
}

void JsonLogger::logInfo(const char* message)
{
    json logData;
    logData["timestamp"] = getISOTime();
    logData["message"] = message;
    logData["type"] = "info";

    std::string dump = logData.dump();

    if (!this->fp) {
        fprintf(stdout, "%s\n", dump.c_str());
    } else {
        fprintf(this->fp, "%s\n", dump.c_str());
        fflush(this->fp);
    }
}

void JsonLogger::logWarning(const char* message)
{
    json logData;
    logData["timestamp"] = getISOTime();
    logData["message"] = message;
    logData["type"] = "warning";

    std::string dump = logData.dump();

    if (!this->fp) {
        fprintf(stdout, "%s\n", dump.c_str());
    } else {
        fprintf(this->fp, "%s\n", dump.c_str());
        fflush(this->fp);
    }
}

void JsonLogger::logError(const char* message)
{
    json logData;
    logData["timestamp"] = getISOTime();
    logData["message"] = message;
    logData["type"] = "error";

    std::string dump = logData.dump();

    if (!this->fp) {
        fprintf(stdout, "%s\n", dump.c_str());
    } else {
        fprintf(this->fp, "%s\n", dump.c_str());
        fflush(this->fp);
    }
}

std::string get_fail_data(const char *message) {
    json jsonData;
    jsonData["error"] = true;
    jsonData["message"] = message;

    std::string data = jsonData.dump();
    return data;
}