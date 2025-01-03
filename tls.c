#include "tls.h"
#include <openssl/ssl.h>
#include <openssl/err.h>

SSL_CTX* create_tls_context(const char *cert_file, const char *key_file) {
    SSL_CTX *ctx = SSL_CTX_new(TLS_server_method());

    if (!ctx) {
        fprintf(stderr, "Failed to create SSL context\n");
        exit(EXIT_FAILURE);
    }

    if (SSL_CTX_use_certificate_file(ctx, cert_file, SSL_FILETYPE_PEM) <= 0 ||
        SSL_CTX_use_PrivateKey_file(ctx, key_file, SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    SSL_CTX_set_alpn_select_cb(ctx, [](SSL *ssl, const unsigned char **out, unsigned char *outlen, const unsigned char *in, unsigned int inlen, void *arg) {
        return SSL_select_next_proto((unsigned char **)out, outlen, in, inlen, (const unsigned char *)"h3", 2);
    }, NULL);

    return ctx;
}