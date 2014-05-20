//============================================================================  
// Name : debug.cpp  
// Author : boyce  
// Version : 1.0  
// Copyright : pku  
// Description : Hello World in C++, Ansi-style  
//============================================================================  
#ifndef MYDEBUG_H_
#define MYDEBUG_H_

#include <stdio.h>  
  
#define __DEBUG__  
  
#ifdef __DEBUG__  
#define DEBUG(format,...) printf("File: "__FILE__", Line: %05d: "format"\n", __LINE__, ##__VA_ARGS__)  
#else  
#define DEBUG(format,...)  
#endif  

#endif
