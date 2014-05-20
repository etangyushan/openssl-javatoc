#include <stdio.h>

int main()
{
		char *line = NULL;
		size_t len = 0;
		
		FILE *pf = fopen("a.txt","r");
		int i=5;
		while(i--)
		{
			getline(&line, &len, pf);
			printf ("buf=%s,size=%d\n", line, len);
		}
}
