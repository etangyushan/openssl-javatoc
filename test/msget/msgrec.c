#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct mymsg
{
	long mtype;
	char buf[256];
};

int main()
{
	key_t key = ftok (".", 100);
	if (key == -1)
	{
		perror ("ftok");
		exit (-1);
	}
	int msgid = msgget (key, 0);
	if (msgid == -1) 
	{
		perror ("msgget");
		exit (-1);
	}
	struct mymsg msg;
	int res = msgrcv (msgid, &msg, sizeof(msg)-4, 2, 0);
	if (res == -1)
	{
		perror ("msgrcv");
		exit (-1);
	}
	printf ("mtype=%ld,msg=%s\n", msg.mtype, msg.buf);

	return 0;
}
