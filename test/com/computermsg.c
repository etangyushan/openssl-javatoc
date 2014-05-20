/* 
 *
 * 作者：司禹
 * */

#include "./computermsg.h"

info_ma computermsg(char* netname)
{
	MEM_OCCUPY mem_stat;
	info_ma data;
	long *ifconfig_result = NULL;  
	char *buf = NULL; 
	char *restr = NULL;

	//获取cpu
	data.cpu = get_cpuuse();
	//获取内存
	data.memory = get_memoccupy ((MEM_OCCUPY *)&mem_stat);
#if 1

	//计算网卡流量
	/*eth0 是计算机上的网卡的名字*/  
	if (NULL == netname)
	{
		netname = "eth0";
	}
	ifconfig_result = my_ipconfig("eth0");  

	/*保存在文件中的数值的单位是B，经过计算换算成MB*/  
	data.get = (double)ifconfig_result[0]/(1024*1024);  

	/*保存在文件中的数值的单位是B，经过计算换算成MB*/  
	data.put = (double)ifconfig_result[1]/(1024*1024);  
#endif

#if 0
	buf = (char*)malloc(1024);
	sDEBUG (buf,"memory:%0.2f, cpu:%0.2f, upload:%0.2f, download:%0.2f",data.memory,data.cpu,data.put,data.get);  
	DEBUG ("buf=%s\n",buf);
#endif

	return data;
}


/*=========CPU========= */
/* 获取cpu的total */
/* 分离出数字 */
int numcapture(char *str, int *cpunum, int size)
{
	int *num = cpunum;
	int sum, flag, i;

	flag = 0;
	sum = 0;
	i = 0;

	while (1)
	{
		if (*str>='0' && *str<='9')
		{
			sum = sum * 10 + (*str - '0');
			str++;
			flag = 1;
		}
		else if (*str >= 'A' && *str <= 'z')
		{
			str++;
			flag = 2;
		}
		else
		{
			if (flag == 1)
			{
				*num = sum;
				sum = 0;
				num += 1;
				flag = 0;
				i++;
			}
			str++;
		}
		if (i >= size)
		{
			return 0;
		}
	}
}

float get_cpuuse () 
{   
	FILE *fp;         
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int num = 0;            
	int i=0;
	int msg[7] = {};
	long int total = 0;
	float cpu;
	CPU_OCCUPY cpust;

	fp = fopen ("/proc/stat", "r"); 
	if(fp<0)
	{
		perror("fopen");
		exit(-1);
	}

	read = getline (&line,&len,fp);
	fclose (fp);
	DEBUG("line=%s,len=%d\n", line, len);
	
#if 1

	int res = numcapture(line, msg, 7);
#endif

#if 1
	cpust.user = msg[0];
	cpust.nice = msg[1];
	cpust.system = msg[2];
	cpust.idle = msg[3];
	cpust.iowait = msg[4];
	cpust.irq = msg[5];
	cpust.softirq = msg[6];
#endif
#if 0
cpu  user=26057 nice=30 system=19540 idle=11578094 6835 108 1405 
	105627
	11683721
#endif
	cpu = 100*(cpust.user + cpust.nice + cpust.system) / (cpust.user + cpust.nice + cpust.system + cpust.idle);
	return cpu;
}

/* ====================网络信息======================== */
long *my_ipconfig(char *ath0)  
{  
	int nDevLen = strlen(ath0);  

	if (nDevLen < 1 || nDevLen > 100)  
	{  

		DEBUG("dev length too long\n");  
		return NULL;  
	}  

	int fd = open("/proc/net/dev", O_RDONLY | O_EXCL);  

	if (-1 == fd)  
	{  
		DEBUG("/proc/net/dev not exists!\n");  
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

	//返回第一次指向ath0位置的指针  
	char* pDev = strstr(buf, ath0);  

	if (NULL == pDev)  
	{  
		DEBUG("don't find dev %s\n", ath0);  
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
		close(fd);  
		free(ifconfig_value);  

	}  

	return rx2_tx10;  
}
/* ==============memory============== */
/* 分离字符串与数字函数 */
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

/* memory信息 */
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
		DEBUG("malloc error\n");
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
	fclose(fl); 
	free(line1);

	return free_total;
}

#if 1
int main()
{
	info_ma buf;
	int i = 1;
	while(1)
	{
		buf = computermsg(NULL);
		DEBUG ("cpu=%f,mem=%f,up=%lf,down=%lf\n", buf.cpu, buf.memory, buf.put, buf.get);
	}
	return 0;
}
#endif
