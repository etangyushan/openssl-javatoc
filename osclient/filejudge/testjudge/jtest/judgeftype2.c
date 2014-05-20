#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "./mydebug.h"

/* 打印所有目录内容 */
int print(char *filename)
{
	DIR *dir = opendir(filename);
	if (dir == NULL) {
		return -1;
	}
	struct dirent *ent;
	chdir(filename);
	while (ent = readdir(dir)) {
		if (strcmp(".", ent->d_name) == 0 || strcmp("..", ent->d_name) == 0) {
			continue;
		}
		if (ent->d_type == 4) {
			DEBUG("[%s]\n", ent->d_name);
			print(ent->d_name);
		} else {
			printf("%s\n", ent->d_name);
		}
	}
	chdir("..");
}

int main()
{
	print("./file");
}
