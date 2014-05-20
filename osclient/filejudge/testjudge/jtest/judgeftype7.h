#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include "./mydebug.h"

/* 1:.doc, 2:.pdf, 3:.ppt */
int filetotxt(char *dirname);

/* 把文件的后缀提取出来 */
char *split_suffix(char *str);
/* 根据后缀判断文件类型 1:.doc, 2:.pdf, 3:.ppt*/
int file_type(char *fname);
