#ifndef __UTILS_H
#define __UTILS_H

#include <stdio.h>
#include<string>

std::string get_health_response();
std::string get_fail_data(const char *message);

class JsonLogger {
private:
    FILE *fp;

public:
    JsonLogger(const char* file_name);
    void logError(const char *message);
    void logWarning(const char *message);
    void logInfo(const char *message);
};

#endif