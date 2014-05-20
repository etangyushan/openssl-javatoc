#include <stdio.h>
#include <string.h>
char *split_suffix(char *str)
{
	int len, tar, i;
	char *new = str;
	//printf ("strlen=%d\n", strlen(str));
	len = strlen(str);
	i = 0;
	while (1) {
		if (*new == '.') {
			i++;
			break;
		}
		new++;
		i++;
	}
	tar = len - i;
	str = str + tar;
	new = str;
	//printf ("%c\n", *str);
	//printf ("%s\n", new);
	return new;
}
