/* 
 * 作者：司禹
 *
 * */


#include "detectorfun.h"

info_ma computerstate(char* netname)
{
	MEM_OCCUPY mem_stat;
	info_ma data;
	long *ifconfig_result = NULL;  
	char *buf = NULL; 
	char *restr = NULL;

	//获取cpu
	data.cpu = get_cpustate();
	data.cpu = 100 - data.cpu;
	/* 获取内存 */
	data.memory = get_memorystate ((MEM_OCCUPY *)&mem_stat);
#if 1

	//计算网卡流量
	/*eth0 是计算机上的网卡的名字*/  
	if (NULL == netname)
	{
		netname = "eth0";
	}
	//ifconfig_result = my_ipconfig("eth0");  
	ifconfig_result =get_networkstate(netname);  

	/*保存在文件中的数值的单位是B，经过计算换算成MB*/  
	data.get = (double)ifconfig_result[0]/(1024*1024);  

	/*保存在文件中的数值的单位是B，经过计算换算成MB*/  
	data.put = (double)ifconfig_result[1]/(1024*1024);  

	/* 计算磁盘使用率空闲到百分比 */
    data.disk = get_diskstate();		
#endif

#if 0
	buf = (char*)malloc(1024);
	sprintf (buf,"memory:%0.2f, cpu:%0.2f, upload:%0.2f, download:%0.2f",data.memory,data.cpu,data.put,data.get);  
	DEBUG ("buf=%s\n",buf);
#endif

	return data;
}

#if 0
int main()
{
	info_ma buf;
	int i = 1;
	while(1)
	{
		buf = computerstate(NULL);
		DEBUG ("cpu=%f,mem=%f,disk=%lf,up=%lf,down=%lf\n", buf.cpu, buf.memory, buf.disk, buf.put, buf.get);
	}
	return 0;
}
#endif
