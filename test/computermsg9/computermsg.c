#include "./computermsg.h"

info_ma computermsg(char* netname)
{
	MEM_OCCUPY mem_stat;
	info_ma data;
	long *ifconfig_result = NULL;  
	char *buf; 
	char *restr = NULL;

	//printf ("size of info_ma=%ld",sizeof (info_ma));
	//	获取内存
	data.memory = get_memoccupy ((MEM_OCCUPY *)&mem_stat);
	data.cpu = get_cpuoccupy();
#if 0
	//第一次获取cpu使用情况
	get_cpuoccupy((CPU_OCCUPY *)&cpu_stat1);
	sleep(1);

	//第二次获取cpu使用情况
	get_cpuoccupy((CPU_OCCUPY *)&cpu_stat2);

	//计算cpu使用率
	data.cpu = cal_cpuoccupy ((CPU_OCCUPY*) &cpu_stat1, (CPU_OCCUPY *)&cpu_stat2);
#endif
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

#if 0
	buf = (char*)malloc(1024);
	sprintf (buf,"memory:%0.2f, cpu:%0.2f, upload:%0.2f, download:%0.2f",data.memory,data.cpu,data.put,data.get);  
//	printf ("buf=%s\n",buf);
#endif

	return data;
}

