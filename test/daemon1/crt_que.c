#include"Apue.h"

int crt_queue()
{
	int msgid;
	while (1) {
		msgid = msgget(VALUE, IPC_CREAT|IPC_EXCL | 0666);
		if ( msgid < 0 && errno == EEXIST ) {
			msgid = msgget(VALUE, 0);
			msgctl(msgid, IPC_RMID, 0);
			errno=0;
			continue;
		}
		else {
			perror("msgget()");
			break;
		}
	}
}


