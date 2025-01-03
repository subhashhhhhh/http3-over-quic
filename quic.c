#include "quic.h"
#include <quiche.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

void handle_quic_connection(uint8_t *buf, ssize_t buf_len, struct sockaddr_in client_addr, socklen_t client_len, int sockfd, SSL_CTX *tls_ctx) {
    quiche_config *config = quiche_config_new(QUICHE_PROTOCOL_VERSION);
    if (!config) {
        fprintf(stderr, "Failed to create quiche config\n");
        exit(EXIT_FAILURE);
    }

    quiche_config_load_cert_chain_from_pem_file(config, "cert.pem");
    quiche_config_load_priv_key_from_pem_file(config, "key.pem");
    quiche_config_set_application_protos(config, (uint8_t *)"h3", strlen("h3"));

    quiche_conn *conn = quiche_accept(NULL, NULL, config);

    if (!conn) {
        fprintf(stderr, "Failed to create quiche connection\n");
        return;
    }

    ssize_t written = quiche_conn_send(conn, buf, buf_len);
    if (written < 0) {
        fprintf(stderr, "Failed to send QUIC packet\n");
        return;
    }

    sendto(sockfd, buf, written, 0, (struct sockaddr *)&client_addr, client_len);
}