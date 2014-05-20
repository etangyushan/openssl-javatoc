#include "computermsg.h"
//memory
unsigned long my_split(char* s1,char** s2)
{
	assert((s1!=NULL) && (s2!=NULL));
	char* s3 = *s2;

	int res = 0;
	for(;;)
	{
		if((*s1 >= '0') && (*s1 <= '9'))
		{
			int j = *s1 - '0';
			res = res * 10 + j;
			s1++;
		}
		else if((*s1 >= 'A') && (*s1 <= 'z'))
		{
			*s3++ = *s1;
			s1++;	
		}
		else if(*s1=='\0')
		{
			break;
		}
		else
		{
			s1++;
			continue;	
		}
	}
	return res;
}

float get_memoccupy (MEM_OCCUPY *mem)
{
	FILE *fl;
	int i;
	float free_total;
	char buff[256];
	MEM_OCCUPY *m;
	m=mem;
	int j;
	unsigned long ret;
	ssize_t n=0;

	char *line;
	char *line1=NULL;
	line1=(char *)malloc(40*sizeof(char));
	if(line1==NULL)
	{
		printf("malloc error\n");
		exit(-1);
	}

	fl = fopen ("/proc/meminfo", "r");
	for( i=0; i<2 ;i++)
	{
		getline(&line,&n,fl);
		ret=my_split(line,&line1);
		if(i==0)
		{
			m->total=ret;
			strcpy(m->name,line1);
			bzero(line1,sizeof(line1));
		}
		if(i==1)
		{
			m->free=ret;
			strcpy(m->name2,line1);
			bzero(line1,sizeof(line1));
		}
	}
	free_total=((float)m->free)/((float)m->total)*100;
//	printf("memory:%f\n",free_total);
	fclose(fl); 
	free(line1);

	return free_total;
}

