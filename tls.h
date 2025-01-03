#ifndef TLS_H
#define TLS_H

#include <openssl/ssl.h>

SSL_CTX* create_tls_context(const char *cert_file, const char *key_file);

#endif