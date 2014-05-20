#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
void print(char *filename)
{
	DIR *dir = opendir(filename);
	if (dir == NULL) return;
	struct dirent *ent;
//	chdir(filename);
	while(ent=readdir(dir))
	{
		if (strcmp(".",ent->d_name) == 0 || strcmp("..",ent->d_name) == 0)
			continue;
		if (ent->d_type == 4)
		{
			printf("[%s]\n",ent->d_name);

			char buf[100] = {};
			strcpy(buf,filename);
			strcat(buf,"/");
			strcat(buf,ent->d_name);
			print(buf);
			/*
			*/
			//print(ent->d_name);
		}
		else
		{
			printf("%s\n",ent->d_name);
			mkdir("dir2.txt",0777);
		}
	}
//	chdir("..");
}

int main()
{
	print("./file");
}
