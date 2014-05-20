#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "./my_syslog.h"

/* 记录匹配的日志和不匹配日志的文件路径 */
#define MATCH "./match.log"
#define NOMATCH "./nomatch.log"

/* 提取名字 */
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

/* 获得文件大小 */
unsigned long get_file_size (const char *path)
{
	unsigned long filesize = -1;
	struct stat statbuff;
	if (stat (path, &statbuff) < 0)
	{
		return filesize;
	}
	else
	{
		filesize = statbuff.st_size;
	}
	return filesize;
}

/* 匹配关键字 */
int seekkey(char *fname, char *keyword)
{
	char command[1024] = {};
	char comgrep[100] = {};
	char name[100] = {};
	char logname[100] = {};
	char msg[100] = {};
	int	size;
	//char *fname = "a.txt";	
	//char keyword[100] = {};

	strcpy (comgrep, "grep -Hni");
	//strcpy (keyword, "tang");
	split_name (fname, name);
	strcpy (logname, fname);
	//strcpy (msg, keyword);
	strcat (name, ".res");
	sprintf (command, "%s %s %s > %s", comgrep, keyword, fname, name);
	system (command);
	
	size = get_file_size(name);
	/* 如果文件为空则说明不匹配  */
	if (0 == size)
	{
		/* 丢掉并记录日志 */
		printf ("丢掉并记录日志\n");
#if 1
		/* 删除a.txt ,没有删除.doc*/
		remove(fname);

		/* 写入日志信息有 文件名，关键字 */
		//strcat (msg, keyword);
		//strcat (msg, " 关键字不匹配");
		sprintf (msg, "关键字 \"%s\"  不匹配\n", keyword);
		my_syslog(NOMATCH, logname, msg);
		return -1;
#endif
	}
	else if (size > 0)
	{
		printf ("匹配并保存\n");
		/* 写入日志信息有 文件名，关键字 */
	//	printf("msg=%s\n", msg);
	//	strcat (msg, " 关键字匹配匹配成功");
	//	sprintf (msg, " %s 关键字匹配成功", keyword);
		sprintf (msg, "关键字 \"%s\" 匹配成功\n", keyword);
		my_syslog(MATCH, logname, msg);
		return 0;
	}
}

int save_match_msg (char *name)
{
#if 0
	FILE *pfile = fopen (name, "rb");
	int size = 0;
	char buf[1024] = {};
	if (pfile)
	{
		while()
		{
			size = fread (buf, sizeof(char), sizeof(buf), pfile);
			if (size == 0)
			{
				perror ("fread");
				break;
			}

			//fwrite (buf, sizeof(char), size, p_file);
		}
	}
	fclose (p_file);
	p_file = NULL;

#endif
	return 0;
}

#if 1
int main()
{
	int res = seekkey ("a.txt", "tang");
}
#endif
