#include "./ssl_server.h"

#define MSGLENGTH 1024
#define PORT 7979
#define MAXCON 8
#define ADDRESS "127.0.0.1"

#define CACERT "../demoCA/private/ca.crt" 
#define SVRCERTF "../demoCA/certs/server.crt" 
#define SVRKEYF "../demoCA/private/server.key" 


SSL *ssl;
msgfile shoumsg;
static int tag = 0;

/* SIGINT信号函数 */
void fa (int signal)
{
	tag = 1;
}

/* 接收线程 */
void *recivefrom_client_pthread (void *p)
{
	DEBUG ("开启接收线程\n");
	char buf[MSGLENGTH]= {};
	int res;
	/* 接收字符串 */
	memset(&shoumsg, 0, sizeof(shoumsg));
	while (1)
	{
		if (tag == 1)
		{
			break;
		}
		//DEBUG ("接收数据...\n");
		res = SSL_read (ssl, &shoumsg, sizeof(shoumsg));
		if (0 >= res)
		{
			perror ("ssl_server.c-41-SSL_read");
			tag = 1;
			break;
		}
		DEBUG ("服务器接收的数据：flag=%d,data=%s,msg=%s\n", shoumsg.flag, shoumsg.stat, shoumsg.msg);
#if 1 
		DEBUG ("shoumsg.flag before change=%d\n", shoumsg.flag);
		switch (shoumsg.flag)
		{
			case 1:
				shoumsg.flag = 2;
				break;
			case 2:
				shoumsg.flag = 3;
				break;
			case 3:
				shoumsg.flag = 4;
				break;
			case 4:
				shoumsg.flag = 1;
				break;
			default:
				shoumsg.flag = 4;
		}
		DEBUG ("shoumsg.flag after change=%d\n", shoumsg.flag);
#endif
	}
	pthread_exit ((void*)1);
}

void sslwrite (int signo)
{
	int res = 0;
	
	if (tag == 1)
	{
		//break;
		pthread_exit((void*)1);		
	//	exit(1);
		DEBUG ("哈哈哈在sslwrite\n");
	}
	res = SSL_write (ssl, &shoumsg, sizeof(shoumsg));
	if (0 >= res)
	{
		perror ("SSL_write");
		tag = 1;
	}
	DEBUG ("服务器发送的数据：flag=%d,data=%s,msg=%s\n", shoumsg.flag, shoumsg.stat, shoumsg.msg);
}

void *sendto_clienthttpsserver_pthread (void *p)
{
	printf ("发送给https服务器...\n");
	signal (SIGALRM, sslwrite);
	//memset(&shoumsg, 0, sizeof(shoumsg));
	struct itimerval tick;
	int sec = 1;
	srand (time(NULL));
	memset (&tick, 0, sizeof(tick));

	//Timeout to run first time
	tick.it_value.tv_sec = sec;
	tick.it_value.tv_usec = 0;

	//After first the Interval time for clock
	tick.it_interval.tv_sec = sec;
	tick.it_interval.tv_usec = 0;

	if (setitimer (ITIMER_REAL, &tick, NULL) < 0)
	{
		perror ("setitimer\n");
	}

	//while (1)
	{
		//sec = rand() % 5;	
		DEBUG ("修改定时器时间%d\n", sec);
		if(-1 == pause());
		{
			DEBUG ("修改定时器时间2%d\n", sec);
		}
	}
	DEBUG ("修改定时器时间3%d\n", sec);
	//pthread_exit((void*)1);		
}


int main ()
{
	SSL_CTX *ctx;
	int sockfd,cli_sockfd;
	int res;

	/* socket文件描述 */
    sockfd = server_socket_init (ADDRESS, PORT, MAXCON);
    cli_sockfd = wait_connect (sockfd);

	/* 初始化ssl */
	/* 为NULL是使用 "RC4-MD5" 加密器*/
	ctx = openssl_init (NULL, CACERT, SVRCERTF, SVRKEYF);

	/* openssl和socket建立连接 */
	ssl = openssl_socket (ctx, cli_sockfd);
	
	DEBUG ("开启读线程\n");
	pthread_t id1, id2;
	pthread_create (&id1, 0, recivefrom_client_pthread, 0);
	//pthread_create (&id2, 0, sendto_clienthttpsserver_pthread, 0);
	signal (SIGINT, fa);
	pthread_join (id1, 0);
	DEBUG ("id1线程退出\n");
	//pthread_join (id2, 0);
	//pthread_detach (id2);
	//DEBUG ("id2线程退出\n");

	/* 关闭资源 */
	DEBUG ("释放资源\n");
	close (sockfd);
	SSL_shutdown (ssl);
	SSL_free (ssl);
	SSL_CTX_free (ctx);
	DEBUG ("服务器关闭。。。\n");
	return 0;
}
