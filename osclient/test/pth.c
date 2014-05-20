#include <stdio.h>


void *p1(void *p)
{	
	int res = 0;
	printf ("线程1.....\n");
	key_t key = ftok (".", 100);
	if (key == -1)
	{
		perror ("ftok")
		exit (-1);
	}
	int msgid = msgget (key, 0);
	if (msgid == -1)
	{
			perror ("msgget");
			exit (-1);
	}
	char buf[100] = {};
	while(1)
	{
		res = msgrcv (msgid, buf, sizeof(buf), 0, 0);	
		if (res == -1)
		{
				perror("msgrcv");
				break;
		}
		printf ("buf=%s, rcv=%d\n", buf, res);
	}
}

void *p2(void *p)
{
    sleep(2);	
	printf ("线程2.....\n");
}

int main()
{
	//int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
	
	pthread_t id1;
	pthread_t id2;
	pthread_create(&id1, 0, p1, 0);
	pthread_create(&id2, 0, p2, 0);
	pthread_joint (id1);
	pthread_joint (id2);

	return 0;
}
