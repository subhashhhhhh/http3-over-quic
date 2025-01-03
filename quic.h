#ifndef QUIC_H
#define QUIC_H

#include <stdint.h>
#include <netinet/in.h>
#include <openssl/ssl.h>

void handle_quic_connection(uint8_t *buf, ssize_t buf_len, struct sockaddr_in client_addr, socklen_t client_len, int sockfd, SSL_CTX *tls_ctx);

#endif