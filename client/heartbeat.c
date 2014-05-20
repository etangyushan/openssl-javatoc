#include <stdio.h>

#define MSGLENGTH 1024 

typedef struct msg
{
	int flag;
	char stat[MSGLENGTH];
	char msg[MSGLENGTH];
} msgfile;

int heartbeat (char *addr, int port, int pid)
{
    info_ma data;
	msgfile hbmsg;
	char buf[256] = {};
	int sockfd = socket_fd (addr, port);

	while (1)
	{
		data = computerstate(NULL);
		sprintf (buf,"memory:%0.2f%%, cpu:%0.2f%%, disk:%0.2%%lf, upload:%0.2fk/s, download:%0.2fk/s", data.memory, data.cpu, data.disk, data.put, data.get);
		strcpy (hbmsg.stat, buf);
		hbmsg.flag = 0;
		strcpy (hbmsg.msg, "Connect is ok ?");
		res = write (sockfd, hbmsg, sizeof(hbmsg));	
		if (res == -1)
		{
			perror("heartbeat.c-26-write");
			break;
		}
		res = read (sockfd, hbmsg, sizeof(hbmsg));	
		if (res == -1)
		{
			perror("heartbeat.c-31-read");
			break;
		}
		if (hbmsg.flag == 0)
		{
			kill (pid, SIGINT);
			break;
		}
	}
	kill (pid, SIGINT);
	close (sockfd);
}

#if 0
int main()
{
	hearbeat();	
}
#endif
