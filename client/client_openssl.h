#ifndef OPENSSL_SERVER_H_
#define OPENSSL_SERVER_H_

#include <stdio.h>	
#include <stdlib.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <errno.h>
#include "./mydebug.h"
	
/* 显示证书信息 */
void show_certs (SSL *ssl);
/* 初始化ssl
   为NULL是使用 "RC4-MD5" 加密器*/
SSL_CTX* openssl_init (char *cipher, char *cacert, char *mycertf, char *mykeyf);

/* openssl和socket建立连接 */
SSL* openssl_socket (SSL_CTX* ctx, int sockfd);

#endif
