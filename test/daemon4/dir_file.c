#include "daemon.h"

int dir_file()
{
	int fd;
	int msgid;
	int ret;
	struct mymsg msg_rcv;

	while(1)
	{
		fd=open("dir_file.txt", O_CREAT | O_EXCL | O_WRONLY, 0666);
		if(errno ==EEXIST && fd <0)
		{
			fd=open("dir_file.txt", O_WRONLY);
			if(fd<0)
			{
				perror("open()");
				exit(-1);
			}
			break;
		}
	}

	msgid=msgget(VALUE,0);
	if(msgid<0)
	{
		perror("msgget()");
		exit(-1);
	}
	while(1)
	{
		bzero(&msg_rcv,sizeof(msg_rcv));
		msgrcv(msgid,&msg_rcv,sizeof(struct mymsg)-sizeof(long),1,0);
		ret=write(fd,msg_rcv.buf,sizeof(msg_rcv.buf));
	}

}
