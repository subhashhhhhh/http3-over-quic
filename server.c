#include "server.h"
#include "tls.h"
#include "quic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "utils.h"

#define MAX_DATAGRAM_SIZE 1350

void run_server(const char *host, int port, const char *cert_file, const char *key_file) {
    SSL_CTX *tls_ctx = create_tls_context(cert_file, key_file);
    int sockfd = create_udp_socket(host, port);

    printf("Server listening on %s:%d\n", host, port);

    uint8_t buf[MAX_DATAGRAM_SIZE];
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    while (1) {
        ssize_t read = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &client_len);
        if (read < 0) {
            perror("recvfrom failed");
            continue;
        }

        handle_quic_connection(buf, read, client_addr, client_len, sockfd, tls_ctx);
    }

    close(sockfd);
    SSL_CTX_free(tls_ctx);
}