#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include "./mydebug.h"

#if 0
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
}

#endif

/* 1:.doc, 2:.pdf, 3:.ppt */
int filetotxt(char *filename)
{
	/* 打开要查找的文件目录 */
	DIR *dir = opendir(filename);
	char fname[1024] = { };
	int flag = 0;
	if (dir == NULL) {
		perror("opendir");
		return false;
	}
	struct dirent *ent = readdir(dir);
	int pos = 0;
	/*  */
	while (1) {
		ent = readdir(dir);
		if (ent == NULL) {
			break;
		}
		if (ent->d_type == 8) {
			/* 判断文件类型 */
			strcpy(fname, ent->d_name);
			flag = file_type(fname);
			switch (flag) {
			case 1:
				//system (catdoc);
				printf("这个是.doc\n");
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
			char buf[100] = { };
			strcpy(buf, filename);
			strcat(buf, "/");
			strcat(buf, ent->d_name);
			printf("buf:%s\n", buf);
			printf("name:%s\n", ent->d_name);
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
	char *new = NULL;
	len = strlen(str);
	tar = len - 4;
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
