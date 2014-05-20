#ifndef SSL_SERVER_H_
#define SSL_SERVER_H_

#include <pthread.h>
#include <curses.h>
#include "./server_socket.h"
#include "./server_openssl.h"
#include "./server_rdwr.h"
#include "./mydebug.h"

typedef struct fafile
{
	int flag;
	char stat[MSGLENGTH];
	char msg[MSGLENGTH];
} msgfile;

void fa (int signal);
void *recivefrom_client_pthread (void *p);
void sslwrite (int signo);
void *sendto_clienthttpsserver_pthread (void *p);

#endif
