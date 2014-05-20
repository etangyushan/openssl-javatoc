#include <stdio.h>
#include <string.h>
int main()
{
	char *str = "fg.doc";
	char buf[1024] = {};
	char *new = str;
	int len, tar;
	len = strlen(new);
	int i = 0;
	while (1) {
		if (*new == '.') {
			break;
		}
		buf[i] = *new++;
		i++;
	}

	printf("buf=%s\n", buf);
}
