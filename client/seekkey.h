#ifndef SEEKKEY_H_
#define SEEKKEY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "./my_syslog.h"
#include <sys/types.h>
#include <dirent.h>
#include "./judgeftype.h"

/* 提取名字 */
int split_name(char *str, char *out);

/* 获得文件大小 */
unsigned long get_file_size (const char *path);

/* 匹配关键字 */
int seekkey(char *fname, char *keyword);

/* 遍历目录中的txt文件 */
int matchfile (char *dirname, char *keywordfile);

/* 从文件全名中把文件的后缀提取出来 */
char *split_suffix(char *str);

/* 提取名字 */
int split_name(char *str, char *out);

#endif
