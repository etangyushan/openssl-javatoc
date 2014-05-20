#ifndef APUE_H
#define APUE_H

#define _FILE_OFFSET_BITS 64
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <glob.h>
#include <sys/mman.h>
#include <time.h>
#include <pwd.h>
#include <shadow.h>
#include <dirent.h>
#include <glob.h>
#include <sys/wait.h>
#include <signal.h>
#include <setjmp.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<syslog.h>
#include<unistd.h>
#include<sys/resource.h>

#define  VALUE (key_t)0xffff

struct msg 
{
	long type;
	char buf[32];
};

#endif
