#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

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
int seekkey(char *fname, char *keyword, char *logfile)
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
	strcpy (msg, keyword);
	strcat (msg, "关键字不匹配");
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
		my_syslog(logfile, logname, msg);
		return -1;
#endif
	}
	else if (size > 0)
	{
		printf ("发送给sftp服务器\n");
		/* 发送给sftp 服务器 */
#if 0
		send_sftp ();
#endif
		return 0;
	}
	else
	{
		return -1;
	}
}

int main()
{
	seekkey ("a.txt", "tang", "bupipei.log");
}
