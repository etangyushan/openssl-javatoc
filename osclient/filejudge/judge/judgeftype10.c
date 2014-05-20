#include "./judgeftype10.h"
#define FILE "./file"

/* 1:.doc, 2:.pdf, 3:.ppt */
int filetotxt(char *dirname)
{
	char name[100] = { };
	char fname[100] = {};
	char comtype[100] = { };
	char buf[100] = { };
	char command[1024] = { };

	int flag = 0;

	/* 打开要查找的文件目录 */
	DIR *dir = opendir(dirname);
	if (dir == NULL) 
	{
		perror("opendir");
		return -1;
	}
		
	struct dirent *ent;
	chdir (dirname);
#if 0
	memset(fname, 0, sizeof(fname));
	memset(buf, 0, sizeof(buf));
	memset(catdoc, 0, sizeof(catdoc));
	memset(command, 0, sizeof(command));
#endif

	/*  */
	while (ent=readdir(dir)) 
	{
		strcpy (name, ent->d_name);
		if (strcmp(".", name) == 0 || strcmp("..", name) == 0)
		{
			continue;
		}
		/* 4 目录文件 */
		if (ent->d_type == 4)
		{
		//	printf("==========[%s]==========\n", name);
			/* 递归调用 */
			filetotxt(name);
		}
		/* 8 文件 */
		else if(ent->d_type == 8) 
		{
			/* 判断文件类型  */
			flag = file_type(name);
			//printf ("flag=%d, name=%s\n", flag, name);

			/* 处理.doc, .pdf, .ppt文件 */
			//printf("command=%s\n", command);

			/* 文件类型flag= 1:.doc, 2:.pdf, 3:.ppt */
			split_name(name, fname);
			//printf("fname=%s\n", fname);
			switch (flag) 
			{
				case 1:
					strcpy(comtype, "catdoc");
					sprintf(command, "%s %s > %s.txt", comtype, name, fname);
					//system (catdoc);
					//printf("这个是.doc: %s\n", command);
					system(command);
					//flag = 0;
					break;
				case 2:
					strcpy(comtype, "pdftotext");
					sprintf(command, "%s %s %s.txt", comtype, name, fname);
					//system (pdftotext);
					//printf("这个是.pdf\n");
					//flag = 0;
					break;
				case 3:
					strcpy(comtype, "ppt");
					sprintf(command, "%s %s > %s.txt", comtype, name, fname);
					//system (ppt);
					//printf("这个是.ppt\n");
					//flag = 0;
					break;
#if 0
				default:
					printf ("此文件不支持: %s\n", command);
					break;
#endif
			}
		}
	}
	chdir ("..");
	return 0;
}
/* 提取文件名 */
int split_name(char *str, char *out)
{
	char buf[100] = {};
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
	//printf("buf=%s\n", buf);
	return 0;
}
/* 把文件的后缀提取出来 */
char *split_suffix(char *str)
{
	//printf ("split_suffix============92\n");
	int len, tar;
	char *new = str;
	len = strlen(new);
	/*  */
	while (1) 
	{
		if (*new == '.') 
		{
			break;
		}
		new++;
	}
	//printf ("new=%s\n", new);
	return new;
}

/* 根据后缀判断文件类型 1:.doc, 2:.pdf, 3:.ppt*/
int file_type(char *fname)
{
	//printf ("file_type============116\n");
	char *suffix = split_suffix(fname);
	//printf ("suffix=%s\n", suffix);
	int flag;
	if (0 == strncmp(suffix, ".doc", 4)) 
	{
		flag = 1;
	}
	else if (0 == strcmp(suffix, ".pdf")) 
	{
		flag = 2;
	}
	else if (0 == strcmp(suffix, ".ppt")) 
	{
		flag = 3;
	}
	else
	{
		flag = 0;
	}

	//printf ("flag=======%d\n", flag);
	return flag;
}

int main()
{
	filetotxt(FILE);
}
