#include "./judgeftype7.h"

/* 1:.doc, 2:.pdf, 3:.ppt */
int filetotxt(char *dirname)
{
	char name[100] = { };
	char catdoc[100] = { };
	char buf[100] = { };
	char command[1024] = { };

	int flag = 0;
	strcpy(catdoc, "catdoc");

	/* 打开要查找的文件目录 */
	DIR *dir = opendir(dirname);
	if (dir == NULL) 
	{
		perror("opendir");
		return -1;
	}
		
	struct dirent *ent;
#if 1
	memset(name, 0, sizeof(name));
	memset(buf, 0, sizeof(buf));
	memset(catdoc, 0, sizeof(catdoc));
	memset(command, 0, sizeof(command));
#endif

	/*  */
	while (ent=readdir(dir)) 
	{
		strcpy (name, ent->d_name);
		strcpy(buf, dirname);
		strcat(buf,"/");
		strcat(buf, name);

		if (strcmp(".", name) == 0 || strcmp("..", name) == 0)
		{
			continue;
		}
		/* 4 目录文件 */
		if (ent->d_type == 4)
		{	
			
			printf("[%s]\n", name);
			/* 递归调用 */
			filetotxt(buf);
			printf ("buf=%s\n", buf);
		}
		/* 8 文件 */
		if (ent->d_type == 8) 
		{
			/* 判断文件类型  */
			flag = file_type(name);
			printf ("flag=%d,name=%s\n", flag, name);
			//flag = file_type(buf);
			/* 处理.doc, .pdf, .ppt文件 */
			sprintf(command, "%s %s > %s.txt", catdoc, buf, buf);
			//printf("command=%s\n", command);

			/* 文件类型flag= 1:.doc, 2:.pdf, 3:.ppt */
			switch (flag) 
			{
				case 1:
					//system (catdoc);
					printf("这个是.doc: %s\n", command);
					//system(command);
					flag = 0;
					break;
				case 2:
					//system (pdftotext);
					printf("这个是.pdf\n");
					flag = 0;
					break;
				case 3:
					//system (ppt);
					printf("这个是.ppt\n");
					flag = 0;
					break;
#if 0
				default:
					printf ("此文件不支持: %s\n", command);
					break;
#endif
			}
		}
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
	while (1) 
	{
		if (*new == '.') 
		{
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

/* 根据后缀判断文件类型 1:.doc, 2:.pdf, 3:.ppt*/
int file_type(char *fname)
{
	char *suffix = split_suffix(fname);
	int flag = 0;
	if (0 == strcmp(suffix, ".doc")) 
	{
		flag = 1;
	}
	if (0 == strcmp(suffix, ".pdf")) 
	{
		flag = 2;
	}
	if (0 == strcmp(suffix, ".ppt")) 
	{
		flag = 3;
	}

	return flag;
}

int main()
{
	filetotxt("./file");
}
