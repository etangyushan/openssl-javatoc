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
	int msgid = msgget (key, 0666|IPC_CREAT);
	if (msgid == -1) 
	{
		perror ("msgget");
		exit (-1);
	}
	struct mymsg msg1 = {1, "hello1"};
	struct mymsg msg2 = {2, "hello2"};
	int res1 = msgsnd (msgid, &msg1, sizeof(msg1)-4, 0);
	int res2 = msgsnd (msgid, &msg2, sizeof(msg2)-4, 0);
	if ((res1 == 0) && (res2 == 0))
	{
		printf ("send ok\n");
	}
	return 0;
}
