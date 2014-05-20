#include "./server_socket.h"
	
int server_socket_init (char *addr, int port, int maxcon)
{

	struct sockaddr_in sin;
	int sockfd;
	int res;

	DEBUG ("Start server...\n");
	/* 创建socket描述符 */
	sockfd = socket (AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		perror("socket");
		return 0;
	}

	/* 清0 */
	memset (&sin, 0, sizeof(sin));
	
	DEBUG("prepare address and port\n");
	/* 准备通信地址和端口号 */
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(addr);
	sin.sin_port = htons(port);

	DEBUG("Begin bind...\n");
	res = bind (sockfd, (struct sockaddr*)&sin, sizeof(sin));
	if (res == -1)
	{
		perror("bind");
		return 0;
	}
	DEBUG ("bind success:address=%s,port=%d\n",addr,port);

	/* 监听设置最大连接数 */
	DEBUG ("listen...\n");
	res = listen (sockfd, maxcon);
	if (-1 == res)
	{
		perror ("listen");
		return 0;
	}

	return sockfd;
}

int wait_connect (int sockfd)
{
	struct sockaddr_in addr_cli;
	int sock_cli;

	socklen_t len = sizeof (addr_cli);

	DEBUG ("wait for client connect...\n");
	/* 等待客户端的连接 */
	sock_cli = accept (sockfd, (struct sockaddr*)&addr_cli, &len);

	char* from = inet_ntoa (addr_cli.sin_addr);

	DEBUG ("client %s connect success\n",from);

	return sock_cli;
}

