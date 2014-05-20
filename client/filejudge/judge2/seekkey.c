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

int main()
{
	char command[1024] = {};
	char comgrep[100] = {};
	char *fname = "a.txt";	
	char name[100] = {};
	char key[100] = {};
	int	size;

	strcpy (comgrep, "grep -Hni");
	strcpy (key, "tang");
		split_name (fname, name);
	strcat(name,".res");
	sprintf (command, "%s %s %s > %s", comgrep, key, fname, name);
	system (command);
	
	size = get_file_size(name);
	/* 如果文件为空则说明不匹配  */
	if (0 == size)
	{
		/* 丢掉并记录日志 */
		printf ("丢掉记录日志\n");
#if 0
		remove(fname);
		syslog();
#endif
	}
	else if (size > 0)
	{
		printf ("发送给sftp服务器\n");
		/* 发送给sftp 服务器 */
#if 0
		send_sftp ();
#endif
	}
	

//	system("grep -Hni '哈哈' a.txt > a.log");
//	system("grep -Hni '呵呵' b.txt > a.log");
}
