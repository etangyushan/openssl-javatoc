#include <stdio.h>
#include <string.h>
int main()
{
	char *str = "basdfasdfasdfc.doc";
	char *new = str;
	int len, tar;
//	printf("strlen=%d\n", strlen(str));
	len = strlen(new);

	while (1) {
		if (*new == '.') {
			break;
		}
		new++;
	}

	printf("*str=%c\n", *str);
	printf("new=%s\n", new);
}
