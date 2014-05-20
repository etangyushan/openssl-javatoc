#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include "./mydebug.h"

/* 1:.doc, 2:.pdf, 3:.ppt */
int filetotxt(char *dirname)
{
	/* 打开要查找的文件目录 */
	DIR *dir = opendir(dirname);
	char fname[1024] = { };
	char catdoc[1024] = { };
	char buf[100] = { };
	char command[1024] = { };

	int flag = 0;
	if (dir == NULL) {
		perror("opendir");
		return false;
	}
	struct dirent *ent = readdir(dir);
	int pos = 0;
	memset(fname, 0, sizeof(fname));
	memset(buf, 0, sizeof(buf));
	memset(catdoc, 0, sizeof(catdoc));
	memset(command, 0, sizeof(command));
	strcpy(fname, ent->d_name);

	/*  */
	while (1) {
		ent = readdir(dir);
		if (ent == NULL) {
			break;
		}
		if (ent->d_type == 8) {
			/* 判断文件类型 */
			flag = file_type(fname);

			/* 处理.doc, .pdf, .ppt文件 */
			strcpy(buf, dirname);
			strcat(buf, "/");
			strcat(buf, fname);
		//	printf("buf=%s\n", buf);
			strcpy(catdoc, "catdoc");
			sprintf(command, "%s %s > %s.txt", catdoc, buf, buf);
			printf("command=%s\n", command);

			switch (flag) {
			case 1:
				//system (catdoc);
				printf("这个是.doc\n");
				system(command);
				break;
			case 2:
				//system (pdftotext);
				printf("这个是.pdf\n");
				break;
			case 3:
				//system (ppt);
				printf("这个是.ppt\n");
				break;
			}
		} else if (ent->d_type == 4 && strcmp(ent->d_name, "..") && strcmp(ent->d_name, ".")) {

			memset(buf, 0, sizeof(buf));
			strcpy(buf, dirname);
			strcat(buf, "/");
			strcat(buf, ent->d_name);
		//	printf("buf:%s\n", buf);
		//	printf("name:%s\n", ent->d_name);
			/* 递归调用 */
			filetotxt(buf);
		}
		pos++;

	}
	return flag;
}

/* 把文件的后缀提取出来 */
char *split_suffix(char *str)
{
	int len, tar;
	int i = 0;
	char *new = str;
	len = strlen(str);
	/*  */
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
	return new;
}

/* 根据后缀判断文件类型 */
int file_type(char *fname)
{
	char *suffix = split_suffix(fname);
	int flag = 0;
	if (0 == strcmp(suffix, ".doc")) {
		flag = 1;
	}
	if (0 == strcmp(suffix, ".pdf")) {
		flag = 2;
	}
	if (0 == strcmp(suffix, ".ppt")) {
		flag = 3;
	}

	return flag;
}

int main()
{
	filetotxt("./file");
}
