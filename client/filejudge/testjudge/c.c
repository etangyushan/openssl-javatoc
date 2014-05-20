#include <stdio.h>
int main()
{
	//system("minihttpdstart.sh");
	FILE *stream = popen ("minihttpdstart.sh", "r");
	pclose (stream);
}
