/*=========CPU========= */
#include "detectorfun.h"
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

CPU_OCCUPY get_cpumsg () 
{   
	FILE *fp;         
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int num = 0;            
	int i=0;
	int msg[7] = {};
	long int total = 0;
	double cpu;
	CPU_OCCUPY cpust;

	fp = fopen ("/proc/stat", "r"); 
	if(fp<0)
	{
		perror("fopen");
		exit(-1);
	}

	read = getline (&line,&len,fp);
	fclose (fp);
	//DEBUG ("line=%s,len=%d\n", line, len);
	
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
	cpu = 100*(cpust.user + cpust.nice + cpust.system) / (cpust.user + cpust.nice + cpust.system + cpust.idle);
	return cpu;
#endif
	return cpust;
}

#if 1
/* top计算cpu方法,比较精确的 */
double get_cpustate()
{
	CPU_OCCUPY cpumsg1 = get_cpumsg ();
	double cputime1 = cpumsg1.user + cpumsg1.nice + cpumsg1.system + cpumsg1.idle + cpumsg1.iowait + cpumsg1.irq + cpumsg1.softirq;
	sleep(1);
	CPU_OCCUPY cpumsg2 = get_cpumsg (); 
	double cputime2 = cpumsg2.user + cpumsg2.nice + cpumsg2.system + cpumsg2.idle + cpumsg1.iowait + cpumsg2.irq + cpumsg2.softirq;
	double user_pass = cpumsg2.user - cpumsg1.user;
	double system_pass = cpumsg2.system - cpumsg1.system;
	double idle_pass = cpumsg2.idle - cpumsg1.idle;
	double usercpurate = user_pass * 100 / (cputime2 - cputime1);
	double systemcpurate = system_pass * 100 / (cputime2 - cputime1);
	double totalcpurate = usercpurate + systemcpurate;
	return totalcpurate;	
}
#endif 

#if 0
double get_cpustate()
{
	CPU_OCCUPY cpumsg1 = get_cpumsg ();
	sleep(1);
	CPU_OCCUPY cpumsg2 = get_cpumsg (); 
	double user_pass = cpumsg2.user - cpumsg1.user;
	double system_pass = cpumsg2.system - cpumsg1.system;
	double idle_pass = cpumsg2.idle - cpumsg1.idle;
	double totalcpurate = (user_pass + system_pass) * 100 / (user_pass + system_pass + idle_pass);
	return totalcpurate;	
}
#endif


#if 0
int main()
{
	while (1)	
	{
		double cpurate = get_cpustate();
		printf ("cpu=%0.2lf\n", cpurate);
	}
}
#endif
