#include"daemon.h"

int main(int argc, char **argv)
{
	int msgid;
	struct mymsg snd_msg;
	snd_msg.type = 1;
	if (argv[1])
	{
		strcpy(snd_msg.buf, "hahaha");
	}
	else
	{
		strcpy(snd_msg.buf, argv[1]);
	}

	printf("%s\n",argv[1]);
	msgid = msgget(VALUE, 0);
	if ( msgid < 0 ) {
		perror("msgget()");
		exit(1);
	}
	msgsnd(msgid, &snd_msg, sizeof(struct mymsg)-sizeof(long), 0);
	printf ("msgsnd success\n");
	return 0;
}

