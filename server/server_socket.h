#ifndef SOCKET_SERVER_H_
#define SOCKET_SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "./mydebug.h"

/* 初始化socket返回服务器的socket描述符 */
int server_socket_init (char *addr, int port, int maxcon);

/* 等待客户端连接返回客户端的socket描述符 */
int wait_connect (int sockfd);

#endif
