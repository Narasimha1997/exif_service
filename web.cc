#include <serving.h>
#include <utils.h>

int main(int argc, char **argv) {
    JsonLogger *logger = NULL;
    if (argc == 2) {
        const char *logging_path = argv[1];
        logger = new JsonLogger(logging_path);
    } else {
        logger = new JsonLogger("logs.json");
    }

    create_server_object(logger);
}