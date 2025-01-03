#include <stdio.h>
#include <stdlib.h>
#include "server.h"

int main(int argc, char **argv) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <host> <port> <cert_file> <key_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *host = argv[1];
    int port = atoi(argv[2]);
    const char *cert_file = argv[3];
    const char *key_file = argv[4];

    run_server(host, port, cert_file, key_file);

    return EXIT_SUCCESS;
}


