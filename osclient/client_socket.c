#include "detectorfun.h"

int socket_fd (char *addr, int port)
{
	struct sockaddr_in sin;
	int sockfd;
	int res;

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
	DEBUG("Begin connect...\n");

	/* 连接服务器 */
	res = connect (sockfd, (struct sockaddr*)&sin, sizeof(sin));
	if (res == -1)
	{
		perror("connect");
		return 0;
	}

	DEBUG ("connect success\n");
	return sockfd;
}
