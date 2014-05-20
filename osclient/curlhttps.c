#include "detectorfun.h"
/* 读取文本文件的数据,发送给服务端的https服务器 */
int mycurl(char *url, char *filename, char param[][10])
{
	CURL *curl;
	CURLcode res;
	char str[4094] = { };
	char newurl[5120] = { };
	FILE *p_file;
	int size;

	/* 读取文本文件中到数据 */
	p_file = fopen(filename, "r");
	if (p_file)
	{
		memset(str, 0, sizeof(str));
		size = fread(str, sizeof(char), sizeof(str), p_file);
		if (0 == size) 
		{
			printf("no data....\n");
		}
	}
	size = strlen(str);
	str[size - 1] = '\0';

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if (curl) 
	{
		/* 生成发送的url */
		//sprintf(newurl, "%s{\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\"}", url, *(param+0), str, *(param+1), "tangtest1", *(param+2), "tangtest2");
		sprintf(newurl, "%s{\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\"}", url, param[0], str, param[1], "tangtest1", param[2], "tangtest2");

		/* 发送数据 */
		curl_easy_setopt(curl, CURLOPT_URL, newurl);

		/* 跳过证书验证 */
		//curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			return 0;
		}

		/* always cleanup */
		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();

	return 0;
}

/* 读取文本文件的数据,发送给服务端的https服务器 */
int mycurlstr(char *url, char msg[][1024], char param[][10])
{
	CURL *curl;
	CURLcode res;
	char str[4094] = {};
	char newurl[5120] = {};
	//int size;

	/* 读取文本文件中到数据 */
	//str[size - 1] = '\0';

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if (curl) 
	{
		/* 生成发送的url */
		//sprintf(newurl, "%s{\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\"}", url, *(param+0), str, *(param+1), "tangtest1", *(param+2), "tangtest2");
		sprintf(newurl, "%s{\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\"}", url, param[0], msg[0], param[1], msg[1], param[2], msg[2]);

		/* 发送数据 */
		curl_easy_setopt(curl, CURLOPT_URL, newurl);

		/* 跳过证书验证 */
		//curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			return 0;
		}

		/* always cleanup */
		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();

	return 0;
}

#if 0
int main(void)
{
	int res = 0;
	char paramstr[][10] = {"param1", "param2", "param3"};
	char msg[][1024] = {"flag", "stat", "policymsg"};
	char *url = "https://10.63.99.185:8443/cnpc_dlp_v_1.0/monitorSet.action?action=receiveData&json=";
	mycurlstr(url, msg, paramstr);
	
#if 0
	char paramstr[][10] = {"data"};
	char *url = "https://10.63.99.176:8443/cnpc_dlp_v_1.0/monitorSet.action?action=receiveData&json=";
	res = mycurl(url, "abc.c", paramstr);
#endif

#if 0
	char *url = "http://10.63.99.185:8080/cnpc_dlp_v_1.0/monitorSet.action?action=receiveData&json=";
	res = mycurl(url, "abc.c", paramstr);
#endif 
	return 0;
}
#endif
