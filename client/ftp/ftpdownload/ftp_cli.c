#include <netinet/in.h>    
#include <sys/types.h>    
#include <sys/socket.h>
#include <netdb.h>    
#include <stdio.h>        
#include <stdlib.h>       
#include <string.h>        

#define SERVER_PORT    12345
#define BUF_SIZE 4096
#define FILE_SIZE 4096
#define CWD_SIZE 4096

int getfile(int s,char file_name[FILE_SIZE],char **argv);
int sendfile(int s,char file_name[FILE_SIZE],char **argv);
int pwdser(int s);
int dirser(int s);
int cdser(int s,char file_name[FILE_SIZE]);
int helpcom(int s);
int quitser(int s);
char buf[BUF_SIZE];
char cwd_buf[CWD_SIZE];
int length;
int offset;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: ./%s server IP address\n",argv[0]);
        exit(1);
    }
    int s;
    char *orders,*p,*words=" \n";
    char order_name[FILE_SIZE];
    char file_name[FILE_SIZE];
    struct sockaddr_in channel;
    channel.sin_family = AF_INET;   
    channel.sin_addr.s_addr = htons(INADDR_ANY);
    channel.sin_port = htons(0);    
    struct sockaddr_in server_addr;
    bzero(&channel,sizeof(channel)); 
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    if(inet_aton(argv[1],&server_addr.sin_addr) == 0) 
    {
          printf("Sorry,You wrote a wrong IP address!\n");
          exit(1);
    }	 
    server_addr.sin_port = htons(SERVER_PORT);
    socklen_t server_addr_length = sizeof(server_addr);
    while(1)
    {    
	    bzero(file_name, FILE_SIZE);
	    bzero(order_name, FILE_SIZE);	   
    	s = socket(AF_INET,SOCK_STREAM,0);
    	if( s < 0)
    	{
        	printf("Can not create socket!\n");
        	exit(1);
    	}

    	if( bind(s,(struct sockaddr*)&channel,sizeof(channel)))
    	{
        	printf("Can not bind port!\n"); 
        	exit(1);
    	}

   	   if(connect(s,(struct sockaddr*)&server_addr, server_addr_length) < 0)
	   {
    	  printf("Can not connect server: %s!, You may wrote a wrong  IP address!\n",argv[1]);
    	  exit(1);
	   }
goagain: 
	printf("ftpclient> ");
	fgets(order_name,FILE_SIZE,stdin);
	orders=strtok(order_name,words);
	if(p=strtok(NULL,words))
		strcpy(file_name,p);
    	if(strcmp(orders,"quit")==0&&*file_name=='\0')
	{
		quitser(s);
		exit(0);
	}
	else if(strcmp(orders,"get")==0&&*file_name!='\0')
		getfile(s,file_name,argv);
	else if(strcmp(orders,"put")==0&&*file_name!='\0')
		sendfile(s,file_name,argv);
	else if(strcmp(orders,"cd")==0&&*file_name!='\0')
		cdser(s,file_name);
	else if(strcmp(orders,"pwd")==0&&*file_name=='\0')
		pwdser(s);
	else if(strcmp(orders,"dir")==0&&*file_name=='\0')
		dirser(s);
	else if((strcmp(orders,"help")==0||strcmp(orders,"?")==0)&&*file_name=='\0')
		helpcom(s);
	else 
	{	
		printf("You wrote a wrong order, please write again!\n");
		goto goagain;
	}	
    close(s);
    }
    return 0;
}

int getfile(int s,char file_name[FILE_SIZE],char **argv)
{
	char order_name[FILE_SIZE]="get&";
	int lengthgth = 0; 
	int write_lengthgth;
	strcat(order_name,file_name);
    bzero(buf,BUF_SIZE);
    strncpy(buf, order_name, strlen(order_name)>BUF_SIZE?BUF_SIZE:strlen(order_name));
    if(send(s,buf,BUF_SIZE,0)<0)
	{
	    printf("Send orders Failed\n");
	    exit(1);
	}
   	bzero(cwd_buf,CWD_SIZE);
    length=strlen(file_name);
    for(offset=length-1;offset>=0 && file_name[offset]!='/';offset--);
	    offset++;
   	getcwd(cwd_buf,sizeof(cwd_buf));
	strcat(cwd_buf,"/");
   	strcat(cwd_buf,(char*)file_name+offset);
    bzero(buf,BUF_SIZE);
    lengthgth = recv(s,buf,BUF_SIZE,0);
    if(lengthgth==0)
 		printf("File not found\n");
    else
    {
		FILE * fp = fopen(cwd_buf,"w");    
    	if(NULL == fp )
    	{
        	printf("Can not open '%s'\n", file_name);
        	exit(1);
    	}
    	do
		{
        	if(lengthgth < 0)
        	{
            	printf("Can not recieve data from server %s !\n", argv[1]);
            	break;
        	}
        	write_lengthgth = fwrite(buf,sizeof(char),lengthgth,fp);
        	if (write_lengthgth < lengthgth)
        	{
            	printf("'%s' write failed\n", file_name);
            	break;
        	}
        	bzero(buf,BUF_SIZE);    
      	 }while( lengthgth = recv(s,buf,BUF_SIZE,0));
    	 printf("Receive '%s' from %s success!\n",file_name, argv[1]); 
    	 fclose(fp);
    }
	return 0;
}

int sendfile(int s,char file_name[FILE_SIZE],char **argv)
{
	char order_name[FILE_SIZE]="put&";
	int read_lengthgth;
	bzero(buf,BUF_SIZE);
	length=strlen(file_name);
    for(offset=length-1;offset>=0 && file_name[offset]!='/';offset--);
	offset++;	
	strcat(order_name,(char*)file_name+offset);
	bzero(buf,BUF_SIZE);
	strncpy(buf, order_name, strlen(order_name)>BUF_SIZE?BUF_SIZE:strlen(order_name));
	if(send(s,buf,BUF_SIZE,0)<0)
	{
	    printf("Send order Failed\n");
	    exit(1);
	}
	FILE * fp = fopen(file_name,"r");
	if(NULL == fp)
	    printf("File not found\n");
	else
	{
	   	bzero(buf, BUF_SIZE);
	   	while( (read_lengthgth = fread(buf,sizeof(char),BUF_SIZE,fp))>0)
	    {
	        if(send(s,buf,read_lengthgth,0)<0)
	        {
	           	printf("Send '%s' Failed\n", file_name);
	           	break;
	       	}
	        bzero(buf, BUF_SIZE);
	    }
        fclose(fp);
        printf("Send '%s' To %s Success!\n",file_name,argv[1]);
        }
	return 0;
}


int pwdser(int s)
{
	char pwdorder[]="pwd&";
	int lengthgth;
	if(send(s,pwdorder,sizeof(pwdorder),0)<0)
	{
	        printf("Send orders Failed\n");
	    	exit(1);
	}
	bzero(buf,BUF_SIZE);
	lengthgth=recv(s,buf,BUF_SIZE,0);
	if(lengthgth < 0)
        {
            	printf("Can not get server's directory!\n");
            	exit(1);
        }
	printf("server directory:%s\n",buf);
	return 0;
}

int dirser(int s)
{
	char dirorder[]="dir&";
	int lengthgth=0;
	if(send(s,dirorder,sizeof(dirorder),0)<0)
	{
	        printf("Send orders Failed!\n");
	    	exit(1);
	}
	bzero(buf,BUF_SIZE);
	while(lengthgth=recv(s,buf,BUF_SIZE,0))
	{
		if(lengthgth<0)
		{
			printf("Error in getting server's dir!\n");
			break;
		}
		printf("\t%s\n",buf);
		bzero(buf,BUF_SIZE);
	}	
	return 0;
}

int quitser(int s)
{
	char quitorder[]="quit&";
	if(send(s,quitorder,sizeof(quitorder),0)<0)
	{
	        printf("Send orders Failed\n");
	    	exit(1);
	}
	return 0;
}

int cdser(int s,char file_name[FILE_SIZE])
{
	char order_name[FILE_SIZE]="cd&";
	strcat(order_name,file_name);
    bzero(buf,BUF_SIZE);
    strncpy(buf, order_name, strlen(order_name)>BUF_SIZE?BUF_SIZE:strlen(order_name));
    if(send(s,buf,BUF_SIZE,0)<0)
	{
	    printf("Send orders Failed\n");
	    exit(1);
	}
	return 0;
}


int helpcom(int s)
{

	char helporder[]="help&";
	if(send(s,helporder,sizeof(helporder),0)<0)
	{
	     printf("Send orders Failed!\n");
	     exit(1);
	}
	printf("get      :get file from the server\n");
	printf("put      :send file to the server\n");
	printf("pwd      :the current directory of the server\n");
	printf("dir      :list the files in the current directory of the server\n");	
	printf("cd       :change the current directory of the server\n");		
	printf("?, help  :list all orderss\n");
	printf("quit     :quit server\n");
	return 0;
}




