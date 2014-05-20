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
		perror("opendir");
		exit(-1);
	}
	struct dirent *ent = readdir(dir);
	int pos = 0;
	while (1) {
		ent = readdir(dir);
		if (ent == NULL) {
			break;
		}
		if (ent->d_type == 8) {
			printf("file=%s\n", ent->d_name);
		} else if (ent->d_type == 4 && strcmp(ent->d_name, "..") && strcmp(ent->d_name, ".")) {
			char buf[100] = { };
			strcpy(buf, filename);
			strcat(buf, "/");
			strcat(buf, ent->d_name);
			printf("buf:%s\n", buf);
			printf("name:%s\n", ent->d_name);
			print(buf);
		}
		pos++;
	}
	return 0;
}

int main()
{
	print("./file");
}
