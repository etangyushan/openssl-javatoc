#include <stdio.h>
#include <string.h>
char* split_name(char *str, char *out)
{
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

	strcpy(out, buf);
	printf("buf=%s\n", buf);
}
int main()
{
	char *str = "fg.doc";
	char new[1024] = {};
	split_name(str, new);
	printf("new=%s\n", new);
}
