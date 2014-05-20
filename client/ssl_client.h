#ifndef SSL_CLIENT_H_
#define SSL_CLIETN_H_

#include <pthread.h>
#include <signal.h>
#include "./client_socket.h"
#include "./client_openssl.h"
#include "./client_rdwr.h"
#include "./my_syslog.h"
#include "./computerstate.h"
#include "./mydebug.h"
#include "./judgeftype.h"
#include "./curlhttps.h"

/* 发送线程 */
void *sendto_https_pthread (void *p);

/* 接收线程 */
void *recivefrom_https_pthread (void *p);

/* 发送到sftp服务器线程 */
void *sendto_sftp_pthread (void *p);

/* 匹配文件线程 */
void *match_file_pthread (void *p);

/* 转换文件线程 */
void *transform_file_pthread (void *p);

void *daemon_pthread (void *p);

void myqueue (int flag);

#endif
