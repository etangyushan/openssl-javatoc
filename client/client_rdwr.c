#include "./client_rdwr.h"

/* 传文件 */
int file_send (SSL *ssl, char *filename)
{

	int fd,res;	
	char sendmsg[MSGLENGTH] = {};
	char revmsg[MSGLENGTH] = {};
	DEBUG("开始文件传输...\n");

    fd = open (filename, O_RDONLY);
	if (fd == -1) 
	{
		perror("open");
	}

	while (1)
	{
		memset (revmsg, 0, sizeof(revmsg));
		res = read (fd, revmsg, sizeof(revmsg));
		if (res <= 0)
		{
			perror("read");
			break;
		}
		res = SSL_write (ssl, revmsg, res);
		if (res < 0)
		{
			perror("SSL_write");
			break;
		}
	}

	memset(sendmsg, 0, sizeof(sendmsg));	
	strcpy(sendmsg, "==END==\n");
	res = SSL_write (ssl, sendmsg, strlen (sendmsg));
	if (res < 0)
	{
		perror("SSL_write");
		return 0;
	}
	DEBUG("snedmsg length=%ld\n", strlen(sendmsg));
	fflush(NULL);

#if 0
	if (-1 == (res = SSL_read (ssl, revmsg, sizeof (revmsg))))
	{
		perror("SSL_read");
		exit(1);	
	}
	revmsg[res] = '\0';
	DEBUG("res = %d\n",res);
	DEBUG ("读到的数据: %s\n", revmsg);
#endif
	DEBUG ("文件传输结束\n");
	close (fd);
	return res;
}

int file_receive (SSL *ssl, char *filename)
{
	int fd, res;
	char revmsg[MSGLENGTH] = {};
	fd = open (filename, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (fd == -1)
	{
		perror("open");
		return -1;
	}
	while (1)
	{
		memset (revmsg, 0, sizeof(revmsg));
		res = SSL_read (ssl, revmsg, sizeof(revmsg));
		if (0 >= res)
		{
			perror ("write");
			break;
		}
	 	res = write (fd, revmsg, strlen(revmsg));
		if (0 >= res)
		{
			perror ("write");
			break;
		}
	}
	DEBUG("revmsg over\n");
	fflush(NULL);
	return 0;
}

/* 传字符串 */
int string_send (SSL *ssl, char *str)
{
	char sendmsg[MSGLENGTH] = {};
	char revmsg[MSGLENGTH] = {};

#if 1
	if (NULL == str)
	{
		while (1)
		{
			memset(sendmsg, 0, sizeof(sendmsg));
			DEBUG ("please input the data to send (input END is over):\n");
			scanf ("%s", sendmsg);
			scanf ("%*[^\n]");
			scanf ("%*c");
			if(strstr(sendmsg, "END"))
			{
				break;
			}
			SSL_write (ssl, sendmsg, strlen (sendmsg));
			fflush(NULL);
		}
	}
	else
	{
		strcpy (sendmsg, str);
		SSL_write (ssl, sendmsg, strlen (sendmsg));
		fflush(NULL);
	}
	//SSL_write (ssl, "==END==\n", strlen ("==END==\n"));
	memset(sendmsg, '\0', sizeof(sendmsg));	
	strcpy(sendmsg, "\r\n");
	SSL_write (ssl, sendmsg, strlen (sendmsg));
	strcpy(sendmsg, "==END==\n");
	SSL_write (ssl, sendmsg, strlen (sendmsg));
	DEBUG("snedmsg length=%ld\n", strlen(sendmsg));
	fflush(NULL);
#endif
	return 0;
}

/* 发结构体 */
int struct_send (SSL *ssl, msgfile famsg)
{
	char sendmsg[MSGLENGTH] = {};
	int res;
	res = SSL_write (ssl, &famsg, sizeof (famsg));
	{
		perror ("SSL_write");
	}
	fflush(NULL);
	memset(sendmsg, '\0', sizeof(sendmsg));	
	strcpy(sendmsg, "\r\n");
	res = SSL_write (ssl, sendmsg, strlen (sendmsg));
	{
		perror ("SSL_write");
	}

	strcpy(sendmsg, "==END==\n");
	res = SSL_write (ssl, sendmsg, strlen (sendmsg));
	{
		perror ("SSL_write");
	}

	fflush(NULL);
	return 0;
}

/* update details */
char *update_details ()
{
		
}
