#ifndef CLIENT_RDWR_H
#define CLIENT_RDWR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "./mydebug.h"

#define MSGLENGTH 1024

/* 传文件 */
int file_send (SSL *ssl, char *filename);

int file_receive (SSL *ssl, char *filename);

/* 传字符串 */
int string_send (SSL *ssl, char *str);

#endif
