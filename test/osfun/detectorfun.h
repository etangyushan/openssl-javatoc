#ifndef OS_H_
#define OS_H_

#include <stdio.h>	
#include <stdlib.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <assert.h>
#include <sys/vfs.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <curl/curl.h>
#include <dirent.h>
#include <stdbool.h>
#include <syslog.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* 显示证书信息 */
void show_certs (SSL *ssl);
/* 初始化ssl
   为NULL是使用 "RC4-MD5" 加密器*/
SSL_CTX* openssl_init (char *cipher, char *cacert, char *mycertf, char *mykeyf);

/* openssl和socket建立连接 */
SSL* openssl_socket (SSL_CTX* ctx, int sockfd);
/* ========client_rdwr.h====== */
#define MSGLENGTH 1024

#if 1
typedef struct msg
{
	int flag;
	char stat[MSGLENGTH];
	char msg[MSGLENGTH];
} msgfile;
#endif

/* 传文件 */
int file_send (SSL *ssl, char *filename);

int file_receive (SSL *ssl, char *filename);

/* 传字符串 */
int string_send (SSL *ssl, char *str);

/* 发结构体 */
int struct_send (SSL *ssl, msgfile famsg); 

/* client_socket */
int socket_fd (char *addr, int port);
	
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


/* 读取文本文件的数据,发送给服务端的https服务器 */
//int mycurl(char *url, char *filename, char **param);
int mycurl(char *url, char *filename, char param[][10]);

/* 1:.doc, 2:.pdf, 3:.ppt */
int filetotxt(char *dirname);

int split_name(char *str, char *out);

/* 把文件的后缀提取出来 */
char *split_suffix(char *str);

/* 根据后缀判断文件类型 1:.doc, 2:.pdf, 3:.ppt*/
int file_type(char *fname);


int my_syslog(char *file, char *logname, char *buf);

  
#define __debug__  
  
#ifdef __debug__  
#define debug(format,...) printf("file: "__file__", line: %05d: "format"\n", __line__, ##__va_args__)  
#else  
#define debug(format,...)  
#endif  

/* 记录匹配的日志的文件路径 */
#define MATCHLOG "/root/detector/log/filematch.log"

/* 记录不匹配日志的文件路径 */
#define NOMATCHLOG "/root/detector/log/filenomatch.log"

/* 存放需要转换的文件目录 */
#define BETRANSFORM "/root/detector/before_transform"

/* 需要匹配的文件目录 */
#define AFTRANSFORM "/root/detector/after_transform"

/* 存放产生到匹配信息的目录 */
#define MATCHDIR "/root/detector/match"

/* 存放客户端日志文件 */
#define MYSYSLOG "/root/detector/log/client.log"

/* 策略关键字文件 */
#define KEYWORD "/root/detector/policy/keyword.plc"

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
