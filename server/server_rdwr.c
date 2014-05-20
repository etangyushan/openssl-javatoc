#include "server_rdwr.h"

/* 发送文件 */
int file_send (SSL *ssl, char *filename)
{
	char sendmsg[MSGLENGTH] = {};
	int fd, res;

	memset (sendmsg, 0, sizeof (sendmsg));
	fd = open ("ser.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("open--148");
	}
	while (1)
	{
		memset (sendmsg, 0, sizeof(sendmsg));
		DEBUG ("Begin SSL_write...\n");
		res = read (fd, sendmsg, sizeof(sendmsg));
		if (res <= 0)
		{
			perror ("read--87");
			break;
		}
		res = SSL_write (ssl, sendmsg, sizeof (sendmsg));
		if(res <= 0)
		{
			ERR_print_errors_fp (stderr);
			break;	
		}
		DEBUG ("string=%s\n", sendmsg);
		if (strstr (sendmsg, "END"))
		{
			break;
		}
	}

	DEBUG ("文件传输结束\n");
	close (fd);
	return res;
}

/* 接收文件 */
int file_receive (SSL *ssl, char *filename)
{

	char revmsg[MSGLENGTH] = {};
	int fd, res;

	memset (revmsg, 0, sizeof (revmsg));
	fd = open (filename, O_CREAT|O_APPEND|O_RDWR, 0666);
	if (fd == -1)
	{
		perror("open--148");
	}
	while (1)
	{
		memset (revmsg, 0, sizeof(revmsg));
		DEBUG ("Begin SSL_read...\n");
		res = SSL_read (ssl, revmsg, sizeof (revmsg));
		if(res <= 0)
		{
			ERR_print_errors_fp (stderr);
			exit (1);
		}
		DEBUG ("string=%s\n", revmsg);
		if (strstr (revmsg, "END"))
		{
			break;
		}
		DEBUG ("Begin write...\n");
		res = write (fd, revmsg, strlen(revmsg));
		if (res <= 0)
		{
			perror ("write--162");
			break;
		}
	}
	close (fd);
	return res;
}

/* 传字符串 */
int string_send (SSL *ssl, char *str)
{
	char revmsg[MSGLENGTH] = {};
	int res;
	strcpy (revmsg, str);
	/* 接收字符串 */
	while (1)
	{
		memset (revmsg, 0, sizeof(revmsg));
		res = SSL_read (ssl, revmsg, sizeof(revmsg));
		if (0 >= res)
		{
			break;
		}
		DEBUG ("receive:%s\n", revmsg);
	}
	return res;
}
