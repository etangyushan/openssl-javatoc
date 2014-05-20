#include <stdio.h>

int main()
{
	char p[][5] = {"aaa", "bbb", "ccc"};	
	printf ("a=%s\n", p);
	printf ("b=%s\n", p[1]);
	printf ("b=%s\n", *(p+1));
	printf ("c=%s\n", *(p+2));
	//printf ("c=%s\n", *p++);
}
