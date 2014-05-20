#ifndef SOCKET_CLIENT_H_
#define SOCKET_CLIENT_H_
	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "./mydebug.h"

int socket_fd (char *addr, int port);
	
#endif
