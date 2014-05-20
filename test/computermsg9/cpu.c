#include "./computermsg.h"

long int get_cputotal (CPU_OCCUPY *cpust) 
{   
	FILE *fp;         
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int num = 0;            
	int msg[7] = {};
	long int total = 0;

	fp = fopen ("/proc/stat", "r"); 
	if(fp<0)
	{
		perror("fopen");
		exit(-1);
	}

	read = getline (&line,&len,fp);
	
#if 1
	char a;
	int i=0;
    int result=0;
	int flag = 1;

	while (flag)
	{
		a = *line;
		if (a >='0' && a<='9')
		{
			result = result * 10 + (a - '0');	
			line++;
		}
		else if (a >= 'A' && a <= 'z') 
		{
			line++;
			continue;
		}
		else if (i >= 7)
		{
			flag = 0;
			break;
		}
		else
		{
			msg[i] = result;
			printf ("result=%d\n", result);
			i++;
			//printf ("i=%d\n", i);
			result = 0;
			if (i >= 7)
			{
				flag = 0;
				break;
			}
			while(1)
			{
				a = *line;
				//if (a >='0' && a<='9' || a=='\0')
				if (a == ' ')
				{
					line++;
					continue;
				}	
				else
				{
					break;
				}
			}
		}
	}
#endif

#if 1
	cpust->user = msg[0];
	cpust->nice = msg[1];
	cpust->system = msg[2];
	cpust->idle = msg[3];
	cpust->iowait = msg[4];
	cpust->irq = msg[5];
	cpust->softirq = msg[6];
#endif

#if 0	
	total = cpust->user + cpust->nice + cpust->system + cpust->idle + cpust->iowait + cpust->irq + cpust->softirq;
	printf ("total=%ld\n",total);
#endif
	for (i=0; i<7; i++)
	{
		total += msg[i];
		//printf ("total=%ld\n",total);
	}
	fclose (fp);
	return total;
}

float cal_cpuoccupy (CPU_OCCUPY *fir, CPU_OCCUPY *sec) 
{   
	float  cpu_use;  

	cpu_use = (100*((sec->user + sec->nice + sec->system)-(fir->user + fir->nice + fir->system)));

	//printf ("cpu_use=%lf\n", cpu_use);
	return cpu_use;
}

float get_cpuoccupy()
{
	CPU_OCCUPY cpust1;
	CPU_OCCUPY cpust2;
	long int total1;
	long int total2;
	float cpu_use;
	total1 = get_cputotal (&cpust1);
	printf ("total1\n");
	sleep (1);
	total2 = get_cputotal (&cpust2);
	printf ("total2\n");
	cpu_use = cal_cpuoccupy (&cpust1, &cpust2);
	cpu_use = cpu_use/(total2 - total1);
#if 0
	printf ("total1=%ld\n", total1);
	printf ("total2=%ld\n", total2);
	printf ("cpu_use=%lf\n", cpu_use);
#endif
	return cpu_use;
}

int main()
{
	 float cpuuser;
	 while(1)
	 {
	 cpuuser = get_cpuoccupy();

	 printf ("cpu=%f", cpuuser);
	 
