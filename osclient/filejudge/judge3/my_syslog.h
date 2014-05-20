#ifndef MY_SYSLOG_H
#define MY_SYSLOG_H

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include "./mydebug.h"

int my_syslog(char *file, char *logname, char *buf);

#endif
