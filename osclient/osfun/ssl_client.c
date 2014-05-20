#include "detectorfun.h"

#if 1
#define port 7979
#define server "127.0.0.1"
#define cacert "../democa/private/ca.crt"
#define mycertf "../democa/certs/client.crt"
#define mykeyf "../democa/private/client.key"
#endif

#define msglength 1024
#define value (key_t)0xffff

SSL *ssl;
int keys;
int tag = 0;
char *httpsurl = "https://10.63.99.185:8443/cnpc_dlp_v_1.0/monitorset.action?action=receivedata&json=";

#if 0
struct mymsg
{
	long mtype;
	char buf[256];
};
#endif

/*  如果结束修改tag为1 */
void fa (int signal)
{
	tag = 1;
}

#if 0
/* 创建消息队列 */
void myqueue (int flag)
{
	int msgid = msgget (value, 0);
	if (msgid == -1)
	{
		perror("msgget");
		exit(-1);
	}

	struct mymsg msg = {1, "我发送数据了"};
	char buf[256] = {};
	sprintf (buf, "%d,%s\n", flag, msg.buf);
	strcpy (msg.buf, buf);
	int res = msgsnd (msgid, &msg, sizeof(msg), 0);
	if (res == -1)
	{
		perror ("msgsend");
		exit (-1);
	}
}
#endif 

/* 发送线程 */
void *sendto_https_pthread (void *p)
{
	printf ("发送到https服务器线程开始...\n");
	msgfile famsg;
	char send_msg[MSGLENGTH] = {};
	char buf[256] = {};
	info_ma data;
	int res;
	int i = 0;
	/* 设置随机数种子 */
	srand (time(0));

	keys = 1;

	/* 检查策略 */
	i = 1;
	while (i--)
	{
		/* 判断是否终止 */
		if (1 == tag)
		{
			printf ("end\n");
			//exit(1);
			break;
		}

		/* 得到计算机状态 */
	    data = computerstate(NULL);
		sprintf (buf,"memory:%0.2f%%, cpu:%0.2f%%, disk:%0.2%%lf, upload:%0.2fk/s, download:%0.2fk/s", data.memory, data.cpu, data.disk, data.put, data.get);
		strcpy (famsg.stat, buf);

		//famsg.flag = keys;
		famsg.flag = rand() % 5;
		switch (famsg.flag)
		{
			case 0:
				strcpy (famsg.msg, "匹配信息0");
				DEBUG("case 0\n");
				break;
			case 1:
				strcpy (famsg.msg, "匹配信息1");
				DEBUG("case 1\n");
				break;
			case 2:
				strcpy (famsg.msg, "匹配信息2");
				DEBUG("case 2\n");
				break;
			case 3:
				strcpy (famsg.msg, "匹配信息3");
				DEBUG("case 3\n");
				break;
			case 4:
				strcpy (famsg.msg, "匹配信息4");
				DEBUG("case 4\n");
				break;
		}
		//DEBUG ("发送数据...\n");
#if 0
		char paramstr[][10] = {"param1", "param2", "param3"};
		char *url = "https://10.63.99.185:8443/cnpc_dlp_v_1.0/monitorSet.action?action=receiveData&json=";
		res = mycurl(url, "abc.c", paramstr);
#endif

#if 1
		//res = mycurl(url, "abc.c", "data");
		//res = mycurl(HTTPSURL, "abc.c", paramstr);
		//char paramstr[][10] = {"data"};
		char paramstr[][10] = {"param1", "param2", "param3"};
		char msg[3][1024] = {};
		//char msg[3][1024] = {"aaa","bbb","ccc"};
#if 0
		strcpy (msg[0], "11111");
		strcpy (msg[1], "22222");
		strcpy (msg[2], "33333");
#endif
		//strcpy (msg[0], famsg.flag);
		sprintf (msg[0], "%d", famsg.flag);
		strcpy (msg[1], "22222");
		//strcpy (msg[1], famsg.stat);
		strcpy (msg[2], famsg.msg);
#if 0

		sprintf (msg[0], "%d", famsg.flag);
		printf ("发送msg0:%s\n", msg[0]);
		sprintf (msg[1], "%s", famsg.stat);
		printf ("发送msg1:%s\n", msg[1]);
		sprintf (msg[2], "%s", famsg.msg);
		printf ("发送msg2:%s\n", msg[2]);
#endif
		res = mycurlstr(httpsurl, msg, paramstr);
		printf ("发送到了https\n");
#endif

#if 0
		res = SSL_write (ssl, &famsg, sizeof(famsg));
		//myqueue (1);
		if (-1 == res)
		{
			perror("SSL_write");
			tag = 1;
			break;
		}
#endif
		//DEBUG ("客户端发送的数据：flag=%d,data=%s,msg=%s\n", famsg.flag, famsg.stat, famsg.msg);

		/* 发送成功使用消息队列给自定义守护进程发消息 */
		//my_syslog (MYSYSLOG, "send_pthread", famsg.msg);
	}
	printf ("发送到https服务器线程结束...\n");
	pthread_exit((void*)1);
}

/* 接收线程 */
void *recivefrom_https_pthread (void *p)
{
	DEBUG ("客户端接收https线程开始...\n");
	int res;
	msgfile shoumsg;
	
	int i = 1;
	while (i--)
	{
		/* 判断是否终止 */
		if (1 == tag)
		{
			//exit(1);
			break;
		}
		/* 从服务端接收 */
		//DEBUG ("客户端接收数据...\n");
		//res = SSL_read (ssl, &shoumsg, sizeof(shoumsg));
		if (-1 == res)
		{
			perror("SSL_read");
			break;
		}
		/* 发送成功使用消息队列给自定义守护进程发消息 */
		//myqueue (2);
		DEBUG ("客户端接收的数据: flag=%d,data=%s,msg=%s\n", shoumsg.flag, shoumsg.stat, shoumsg.msg);
		/* 接受成功使用消息队列给自定义守护进程发消息 */
		//my_syslog (MYSYSLOG, "recive_pthread", shoumsg.msg);
		/* 改变策略 */
		//DEBUG ("keys befor change=%d\n", keys);
		switch (shoumsg.flag)
		{
			case 1:
				keys = 1;
				break;
			case 2:
				keys = 2;
				break;
			case 3:
				keys = 3;
				break;
			case 4:
				keys = 4;
				break;
		}
		//DEBUG ("keys after change=%d\n", keys);
	}
	DEBUG ("客户端接收https线程结束...\n");
	pthread_exit((void*)1);
}

#if 0
/* 启动自定义守护进程  */
void *daemon_pthread (void *p)
{
	DEBUG ("启动守护进程\n");
	pid_t pid = vfork();
	if (pid == 0)
	{
		//mydaemon();	
	//	execl ("./","mydaemon");
	}
	/* 判断是否终止 */
	if (tag)
	{
		pthread_exit((void*)1);
	}
}
#endif

/* 发送到sftp服务器线程 */
void *sendto_sftp_pthread (void *p)
{
	printf ("发送到sftp服务器线程开始...\n");

	printf ("向sftp发送数据\n");

	printf ("发送到sftp服务器线程结束...\n");
	pthread_exit((void*)1);
}

/* 匹配文件线程 */
void *match_file_pthread (void *p)
{
	printf ("匹配文件线程开始...\n");

	/* 调用匹配函数，将匹配目录下的所有文件 */
	int res = matchfile (AFTRANSFORM, KEYWORD);

	printf ("匹配文件线程结束...\n");
	pthread_exit((void*)1);
}

/* 转换文件线程 */
void *transform_file_pthread (void *p)
{
	printf ("转换文件线程开始...\n");

	filetotxt (BETRANSFORM);

	printf ("转换文件线程结束...\n");
	pthread_exit((void*)1);
}

/* 心跳 */
void *heartbeat_pthread(int *p)
{
	pid_t pid = *p;
	printf ("pid = %d\n", pid);
	//hearbeat (addr, port, pid);		
}

int main ()
{
	printf ("启动客户端。。。\n");
#if 0
	int sockfd;
	int res;
	SSL_CTX *ctx;

	DEBUG ("初始化客户端...\n");
	/* 自定义信号函数 */
	signal (SIGINT, fa);
	
	sockfd = socket_fd (SERVER, PORT);
	/* 初始化ssl 
	   为NULL是使用 "RC4-MD5" 加密器 */
	ctx = openssl_init (NULL, CACERT, MYCERTF, MYKEYF);
	
	/* openssl和socket建立连接 */
	ssl = openssl_socket (ctx, sockfd);
	DEBUG ("客户端初始化完毕\n");
#endif

#if 0
	printf ("启动minihttpd服务器...\n");
	system ("minihttpdstart.sh");
#endif 

#if 0
	pid_t pid = vfork ();
	pid_t minihttpdpid;
	if (pid == 0)
	{
		//minihttpdpid = getpid();
	    printf ("启动minihttpd........\n");	
		execl ("/mini_httpdstart.sh", "mini_httpdstart.sh","./"NULL);
		printf ("minihttpdpid=%d\n", minihttpdpid);
		printf ("启动minihttpd服务器完成\n");
	}
#endif
	
#if 0
	/* 获取客户端证书信息 */
	printf ("SSL connection using %s\n", SSL_get_cipher (ssl));
	X509 *server_cert = SSL_get_peer_certificate (ssl);
	printf ("Server certificate:\n");
	char *str = X509_NAME_oneline (X509_get_subject_name (server_cert),0,0);
	printf ("\t subject: %s\n", str);
	OPENSSL_free (str);
	str = X509_NAME_oneline (X509_get_issuer_name  (server_cert),0,0);
	printf ("\t issuer: %s\n", str);
	OPENSSL_free (str);  
	X509_free (server_cert);
#endif
	
	/* 创建接收https线程，发送到https线程,发送到sftp线程,匹配文件线程 */
	pthread_t id1, id2, id3, id4, id5, id6;
	//pthread_t id1, id2, id3;

#if 1
	/* 创建发送到https线程 */
	pthread_create (&id1, 0, sendto_https_pthread, 0);
	/* 创建接收https线程 */
	pthread_create (&id2, 0, recivefrom_https_pthread, 0);
	/* 创建发送到sftp线程 */
	pthread_create (&id3, 0, sendto_sftp_pthread, 0);
	/* 创建匹配文件线程 */
	pthread_create (&id4, 0, match_file_pthread, 0);
#endif
	/* 创建转换文件线程 */
	pthread_create (&id5, 0, transform_file_pthread, 0);
	
	/* 创建心跳线程 */
	pid_t pid = getpid();
	pthread_create (&id6, 0, heartbeat_pthread, (void*)&pid);
#if 1
	pthread_join (id1, 0);
	pthread_join (id2, 0);
	pthread_join (id3, 0);
	pthread_join (id4, 0);
#endif
	pthread_join (id5, 0);
	pthread_join (id6, 0);

	/* 关闭资源 */
#if 0
	DEBUG ("资源释放...\n");
	close (sockfd);
	SSL_shutdown (ssl);
	SSL_free (ssl);
	SSL_CTX_free (ctx);
	DEBUG ("客户端关闭...\n");
#endif
	printf ("客户端退出。。。\n");
	return 0;
}
