#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "./mydebug.h"

int main()
{
	DIR *dir = opendir("./file");
	if (dir == NULL) {
		perror("opendir");
		exit(-1);
	}
	while (1) {
		struct dirent *ent = readdir(dir);
		if (ent == NULL) {
			break;
		}
		DEBUG("%d,%s\n", ent->d_type, ent->d_name);
	}
}
