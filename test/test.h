/**
 需要打印的地方使用 DEBUG()函数，使用方法和printf()一样;
 在程序中添加 #define __DEBUG__ 这个宏,表示打印信息,注释后则不打印
 * */
#ifndef MYDEBUG_H_
#define MYDEBUG_H_

#include <stdio.h>
#define __DEBUG__
#ifdef __DEBUG__
//#define DEBUG(format,...) printf("File:"__FILE__", Line:%05d: "format"\n", __LINE__, ##__VA_ARGS__)

#define DEBUG(format,...) printf("File: "__FILE__", Line: %05d: "format"\n", __LINE__, ##__VA_ARGS__)  
#else
#define DEBUG(format...)
#endif

#endif
