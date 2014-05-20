#ifndef PROJECT1_H_
#define PROJECT1_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<unistd.h>
#include "./mydebug.h"


typedef  struct PACKED
{
	char name[20];
	unsigned int user;
	unsigned int nice;
	unsigned int system;
	unsigned int idle;
	unsigned int iowait;
	unsigned int irq;
	unsigned int softirq;
} CPU_OCCUPY;

typedef struct PACKED1
{
	char name[20];
	unsigned long total;
	char name2[20];
	unsigned long free;
} MEM_OCCUPY;

typedef struct sent_info
{
	float cpu;
	float memory;
	double put;
    double  get;

} info_ma;


/*cpu*/
float get_cpuuse ();
int numcapture(char *str, int *cpunum, int size);

//eth0
long *my_ipconfig(char *ath0);  

//memory
unsigned long my_split(char* s1,char** s2);

float get_memoccupy (MEM_OCCUPY *mem);

unsigned long my_split(char* s1,char** s2);

/* 得到计算机信息 */
info_ma computermsg(char *netname);

#endif
