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
#include <stdlib.h>  
#include<sys/vfs.h>
#include <sys/time.h>
#include <sys/resource.h>
#include<errno.h>

/* 磁盘信息相关 */
typedef struct 
{
	double	 total_size;
	double	 total_root;
	double	 total_swap;
	double	 total_home;
} hadd;

typedef struct node 
{
	long free_root;
	long free_home;
}free_hadd;

/* cpu信息相关 */
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


/* 计算机总体状态  */
typedef struct sent_info
{
	double cpu;
	double memory;
    double disk;
	double put;
    double get;

} info_ma;


/* cpu使用信息 */
int numcapture(char *str, int *cpunum, int size);
CPU_OCCUPY get_cpumsg (); 
double get_cpustate();

/* network state 网络状态 */
long *get_networkstate(char *ath0);  

/* memory使用信息 */
unsigned long my_split(char* s1,char** s2);
unsigned long my_split(char* s1,char** s2);

/* 接口函数,返回内存使用率 */
double get_memorystate (MEM_OCCUPY *mem);


/* 磁盘使用信息 */
double rest_hdd();
int divie_num(char *line,int flag);
int f_open(char *filename);
/* 接口函数,返回磁盘使用率 */
double get_diskstate();  

/* 得到计算机信息,cpu使用率,内存占用，磁盘占用，网络上行、下行流量 */
info_ma computerstate();

#endif
