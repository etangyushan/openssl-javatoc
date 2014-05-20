#include "./seekkey.h"
#include "./mydir.h"

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
		return filesize;
	}
}

/* 匹配关键字 */
int seekkey(char *fullname, char *keyword)
{
	char command[1024] = {};
	char filename[256] = {};
	char matchfile[256] = {};
	char logmsg[100] = {};
	int	size = 0;

	/* 丢掉文件名后缀 */
	split_name (fullname, filename);
	sprintf (matchfile, "%s/%s.match", MATCHDIR, filename);
	sprintf (command, "grep -Hni %s %s/%s >> %s", keyword, AFTRANSFORM, fullname, matchfile);
	//printf ("command:%s\n", command);
	system (command);
	
	size = get_file_size(matchfile);
	/* 如果文件为空则说明不匹配  */
	if (0 == size)
	{
		/* 丢掉并记录日志 */
		printf ("丢掉并记录日志\n");
#if 0
		/* 删除a.txt ,没有删除.doc */
		remove (filename);
		remove (name);

#endif
		/* 写入日志信息有 文件名，关键字 */
		memset (logmsg, 0, sizeof(logmsg));
		sprintf (logmsg, "关键字 \"%s\"  不匹配\n", keyword);
		my_syslog(NOMATCHLOG, filename, logmsg);
		return -1;
	}
	else if (size > 0)
	{
		printf ("匹配并保存\n");
		/* 写入日志信息有 文件名关键字 */
		memset (logmsg, 0, sizeof(logmsg));
		sprintf (logmsg, "关键字 \"%s\" 匹配成功\n", keyword);
		my_syslog(MATCHLOG, filename, logmsg);
	}
	return 0;
}

/* 对目录下的.txt文件进行匹配 */
int matchfile (char *dirname, char *policyfile)
{
	char savefilename[256][256] = {};
	char keyword[256] = {};
	char *suffix;
	FILE *p_file;
	char *line;
	size_t len = 0;
	int res = 0;
	int i = 0;

	memset(savefilename, 0, sizeof(savefilename));
	p_file = fopen (policyfile, "r");
	if (p_file == NULL)
	{
		perror("seekkey.c-99-fopen");
		return -1;
	}

	/* 打开要进行匹配的文件目录 */
	DIR *dir = opendir(dirname);
	if (dir == NULL) 
	{
		perror("seekkey.c-98-opendir");
		return -1;
	}
		
	struct dirent *ent;
	/* 遍历目录下的文件 */
	while (1) 
	{	
		ent=readdir(dir);
		if (ent <= 0)
		{
			break;
		}
		if ((strcmp(".", ent->d_name)==0) || (strcmp("..", ent->d_name)==0) || (ent->d_type == 4))
		{
			continue;
		}
		/* 文件是.txt的文件就进行匹配 */
		else if(ent->d_type == 8)
		{
			suffix = split_suffix (ent->d_name);
			//printf ("seekkey.c-suffix-112:%s\n", suffix);	
			//printf ("seekkey.c-d_name-114:%s\n", ent->d_name);	
			if (strcmp(suffix, ".txt") == 0)
			{
				strcpy (savefilename[len++], ent->d_name);
			}
		}
	}

	/* 获取关键字 */
	while (getline(&line, &len, p_file) != -1)
	{
		strcpy (keyword, line);
	    res = strlen (keyword);
	    keyword[res-1]='\0';
#if 1
	    i = 0;
		printf ("===============keyword:%s================\n", keyword);
	    while (strlen(savefilename[i]) != 0)	
	    {
	        seekkey (savefilename[i], keyword);
			printf ("seekkey.c-157-savefilename[%d]:%s\n", i, savefilename[i]);
			//printf ("===================%d==================\n", i);
			i++;
	    }
#endif
	}
	if (line)
	{
	   free(line);
	   line = NULL;
	}

	fclose(p_file);
	p_file = NULL;
	closedir (dir);
	return 0;
}

#if 0
int main()
{
	char my_path[1024] = {};
	/* int res = seekkey ("a.txt", "tang"); */
#if 1
	char *fpath;
	fpath=(char *)malloc(256);
	getcwd(fpath, 256);
	//printf("路径%s",fpath);
#endif
	char *dirname = "file";
	char *keywordfile = "keyword.log";
	sprintf (my_path, "%s/%s", fpath, dirname);
	//int res = matchfile (dirname, keywordfile);
	int res = matchfile (my_path, keywordfile);
}
#endif
