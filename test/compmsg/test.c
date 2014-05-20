#include <stdio.h>
#include "computermsg.h"

int main()
{
	char *buf;
	buf = computermsg(NULL);
	printf ("buf=%s\n", buf);
	return 0;
}
