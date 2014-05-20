/*cpu*/
#include "computermsg.h"
void get_cpuoccupy (CPU_OCCUPY *cpust) 
{   
	FILE *fd;         
	int num=0;            
	CPU_OCCUPY *cpu_occupy;
	cpu_occupy=cpust;
	int str[10]={0};
	char *p[10];
	char *ptmp;
	char *line=NULL;
	ssize_t n;
	int i;
	int m=0;
	int j=0;

	fd = fopen ("/proc/stat", "r"); 
	if(fd<0)
	{
		perror("fopen()");
		exit(-1);
	}

	getline(&line,&n,fd);
	for( i=0; i<10; i++)
	{
		p[i]=(char *)malloc(10*sizeof(char));
		
		if(p[i]==NULL)
		{
			printf("malloc error\n");
			exit(-1);
		}
		
	}
	for( i=0;line[i]!='\0';i++)
	{

		if((line[i]>='0')&&(line[i]<='9'))
		{

			ptmp=line+i;
			while(*(line+i))
			{
				m++;
				i++;
				if(line[i]==' ')
				{
					break;
				}
			}
			strncat(p[j],ptmp,m);
			*(p[j]+m)='\0';
			j++;
			m=0;
		}
	}
	cpu_occupy->user = atoi(p[0]);
	cpu_occupy->nice = atoi(p[1]);
	cpu_occupy->system = atoi(p[2]);
	cpu_occupy->idle = atoi(p[3]);	
	cpu_occupy->iowait=atoi(p[4]);
	cpu_occupy->irq=atoi(p[5]);
	cpu_occupy->softirq=atoi(p[6]);

	for( i=0; i<10; i++)
	{
		if(p[i]!=NULL)
		{
			bzero(p[i],10);
		}

	}
}

int cal_cpuoccupy (CPU_OCCUPY *o, CPU_OCCUPY *n) 
{   
	unsigned long od, nd;    
	unsigned long id, sd;
	float  cpu_use = 0;   
	unsigned long  num1=0,num2=0;

	od = (unsigned long) (o->user + o->nice + o->system + o->idle + o->irq + o->softirq + o->iowait);
	nd = (unsigned long) (n->user + n->nice + n->system + n->idle + n->irq + n->softirq + o->iowait);
	id = (unsigned long) (nd-od); 
	sd = (unsigned long) (n->idle - o->idle);
	if(id != 0)
	{
		cpu_use=(int)((sd*100)/id);
	}

	return cpu_use;
}
//eth0
long *my_ipconfig(char *ath0)  

{  
	int nDevLen = strlen(ath0);  

	if (nDevLen < 1 || nDevLen > 100)  

	{  

		printf("dev length too long\n");  
		return NULL;  
	}  

	int fd = open("/proc/net/dev", O_RDONLY | O_EXCL);  

	if (-1 == fd)  

	{  

		printf("/proc/net/dev not exists!\n");  

		return NULL;  

	}  



	char buf[1024*2];  

	lseek(fd, 0, SEEK_SET);  

	int nBytes = read(fd, buf, sizeof(buf)-1);  

	if (-1 == nBytes)  

	{  

		perror("read error");  

		close(fd);  

		return NULL;  

	}  

	buf[nBytes] = '\0';  

//	返回第一次指向ath0位置的指针  

		char* pDev = strstr(buf, ath0);  

	if (NULL == pDev)  

	{  

		printf("don't find dev %s\n", ath0);  

		return NULL;  

	}  

	char *p;  

	char *ifconfig_value;  

	int i = 0;  

	static long rx2_tx10[2];  

	/*去除空格，制表符，换行符等不需要的字段*/  

	for (p = strtok(pDev, " \t\r\n"); p; p = strtok(NULL, " \t\r\n"))  

	{  

		i++;  

		ifconfig_value = (char*)malloc(20);  

		strcpy(ifconfig_value, p);  

		/*得到的字符串中的第二个字段是接收流量*/  

		if(i == 2)  

		{  

			rx2_tx10[0] = atol(ifconfig_value);  

		}  

		/*得到的字符串中的第十个字段是发送流量*/  

		if(i == 10)  

		{  

			rx2_tx10[1] = atol(ifconfig_value);  

			break;  

		}  

		free(ifconfig_value);  

	}  

	return rx2_tx10;  

}  

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

//main
int main()
{
	CPU_OCCUPY cpu_stat1;
	CPU_OCCUPY cpu_stat2;
	MEM_OCCUPY mem_stat;
	static info_ma data;
//	int cpu;
	long *ifconfig_result;  
//	double re_mb;  
	//	获取内存
	data.memory=get_memoccupy ((MEM_OCCUPY *)&mem_stat);

	//第一次获取cpu使用情况
	get_cpuoccupy((CPU_OCCUPY *)&cpu_stat1);
	sleep(1);
	//第二次获取cpu使用情况
	get_cpuoccupy((CPU_OCCUPY *)&cpu_stat2);
	//计算cpu使用率
	data.cpu= cal_cpuoccupy ((CPU_OCCUPY*) &cpu_stat1, (CPU_OCCUPY *)&cpu_stat2);
	//printf("cpu=%d\n",cpu);

	//计算网卡流量
	/*eth0 是博主计算机上的网卡的名字*/  
	ifconfig_result = my_ipconfig("eth0");  
	/*保存在文件中的数值的单位是B，经过计算换算成MB*/  
	data.get= (double)ifconfig_result[0]/(1024*1024);  
	/*保存在文件中的数值的单位是B，经过计算换算成MB*/  
	data.put = (double)ifconfig_result[1]/(1024*1024);  
	printf("memory:%0.2f cpu:%d put:%0.2f get:%0.2f\n",data.memory,data.cpu,data.put,data.get);  
	char buf[1024] = {};
	sprintf (buf,"memory:%0.2f cpu:%d put:%0.2f get:%0.2f\n",data.memory,data.cpu,data.put,data.get);  
	printf ("buf=%s\n",buf);
	return 0;
}

