#include <stdlib.h>  
#include <stdio.h>  
#include <unistd.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include<strings.h>
#include<string.h>
#include<sys/vfs.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include<errno.h>

typedef struct 
{
	double	 total_size;
	double	 total_root;
	double	 total_swap;
	double	 total_home;
} hadd;

typedef struct node 
{
	long free_root;
	long free_home;
}free_hadd;

static hadd data;
static free_hadd rt_da;
double rest_hdd()
{
	int ret;
	struct statfs sfs;
	double percent;
	double result;
	char *p[2]={"/home","/root"};
	int i;
	for( i=0; i<2; i++)
	{
		ret=statfs(p[i],&sfs);
		if(ret<0)
		{
			perror("statfs()");
			break;
		}
#if 0
		percent=(sfs.f_blocks-sfs.f_bfree)*100/(sfs.f_blocks-sfs.f_bfree+sfs.f_bavail)+1;
		printf("%s %ld %ld %d %ld %%\n",p[i],4*sfs.f_blocks,4*(sfs.f_blocks-sfs.f_bfree),4*sfs.f_bavail,percent);
#endif	
		switch(i)
		{
			case 0:rt_da.free_root=(4*sfs.f_blocks)/(1024*1024);
				   break;
			case 1:rt_da.free_home=(4*sfs.f_blocks)/(1024*1024);
				   break;
			default:
				   ;break;
			
		}
	}
	percent=rt_da.free_root+rt_da.free_home;
	result=percent/data.total_size;
	//printf("total_size:%0.2lf  rest_size:%0.2lf  percentage:%0.2lf%\n",data.total_size,percent,result*100);

	return (100-result*100);
}
#if 0
int print()
{
	printf("%lf %lf %lf %lf\n",data.total_size, data.total_root,data.total_swap,data.total_home);
	return 0;
}

#endif
int divie_num(char *line,int flag)
{
	char str[100]={0};
	char *p1=NULL;
	int i;
	p1=line;
	
	for( i=0; i<strlen(line); i++)
	{
		if(line[i]==',')
		{
			break;
		}
		if(('0'<=line[i] && line[i]<='9') || (line[i]=='.'))
		{
			str[strlen(str)]=line[i];
		}
	
	}
	str[strlen(str)]='\0';

	switch(flag)
	{
		case 0:data.total_size=atof(str);
					break;
		case 1: data.total_root=atof(str);
					break;
		case 2: data.total_swap=atof(str);
					break;
		case 3: data.total_home=atof(str);
					break;
		default:	
					 break;
	}
	return 0;
}

int f_open(char *filename)
{
	FILE *fp;
	size_t n=50;
	int i=10;
	char *line=NULL;
	size_t ret;
	int flag=0;
	char buf[]="Disk /dev/";

	fp=fopen(filename,"r");
	if(fp==NULL)
	{
		fp=fopen(filename,"r");
		if(fp==NULL)
		{
			printf("<%d>\n",__LINE__);
			perror("fopen()");
			exit(-1);
		}
	}

	while(1)
	{
		ret=getline(&line,&n,fp);
		if(ret==-1)
		{
			break;
		}
		for( i=0; i<10; i++)
		{
			if(line[i]==buf[i])
			{
				if(i>8)
				{
					divie_num(line,flag);
					flag++;
				}
			}
			else
			{
				break;
			}
		}
	}
	fclose(fp);
	return 0;
}

double hdd()  
{  
	int tty;
	int fd ;
	int save_fd;
	static hadd total;
#if 1	
	fflush(stdout);  
	setvbuf(stdout,NULL,_IONBF,0);  
	save_fd = dup(STDOUT_FILENO);  
	fd = open("hddmsg.log",(O_WRONLY | O_CREAT | O_TRUNC), 0666);  
	if(fd<0)
	{
		printf("<%d>\n",__LINE__);
		perror("open()");
		exit(-1);
	}

	dup2(fd,STDOUT_FILENO);  
	system("fdisk -l");
	dup2(save_fd,STDOUT_FILENO);  
	dup2(STDOUT_FILENO,save_fd);  
	close(save_fd);
	usleep(1000);
	close(fd);
	f_open("hddmsg.log");
#endif 
	return rest_hdd();
}  
#if 0
int main()  
{
	printf ("hdd=%lf\n", hdd());
}
#endif
