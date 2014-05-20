#include <stdio.h>
#include <sys/stat.h>

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
	//unsigned long size = get_file_size("a.txt");
	unsigned long size = get_file_size("b.log");
	printf ("size = %ld\n", size);
}
