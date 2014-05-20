#ifndef CURLHTTPS_H_
#define CURLHTTPS_H_

#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

/* 读取文本文件的数据,发送给服务端的https服务器 */
//int mycurl(char *url, char *filename, char **param);
int mycurl(char *url, char *filename, char param[][10]);

#endif
