/* ====================网络信息======================== */
#include "./computerstate.h"

long *get_networkstate(char *ath0)  
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
