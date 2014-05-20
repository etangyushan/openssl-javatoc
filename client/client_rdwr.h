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
//#include "computermsg.h"
#include "./mydebug.h"

#define MSGLENGTH 1024

#if 1
typedef struct msg
{
	int flag;
	char stat[MSGLENGTH];
	char msg[MSGLENGTH];
} msgfile;
#endif

/* 传文件 */
int file_send (SSL *ssl, char *filename);

int file_receive (SSL *ssl, char *filename);

/* 传字符串 */
int string_send (SSL *ssl, char *str);

/* 发结构体 */
int struct_send (SSL *ssl, msgfile famsg); 

#endif
