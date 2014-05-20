#include "computermsg.h"

int main()
{
	//char *buf;
	info_ma buf;
	while(1)
	{
		buf = computermsg(NULL);
		printf ("cpu=%f,mem=%f,up=%lf,down=%lf\n", buf.cpu, buf.memory, buf.put, buf.get);
	}
	return 0;
}
