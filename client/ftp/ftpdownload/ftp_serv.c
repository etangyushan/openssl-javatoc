#include <netdb.h>
#include <netinet/in.h>   
#include <sys/types.h>    
#include <sys/socket.h>    
#include <stdio.h>        
#include <stdlib.h>       
#include <string.h>        
#include <dirent.h>
#include <unistd.h>

#define SERVER_PORT    12345
#define BUF_SIZE 4096
#define FILE_SIZE 4096
#define CWD_SIZE 4096
#define QUEUE_SIZE 10

int getfile(int new_sock,char file_name[FILE_SIZE]);
int sendfile(int new_sock,char file_name[FILE_SIZE]);
int quitser();
int cdser(char file_name[FILE_SIZE]);
int pwdser(int new_sock);
int dirser(int new_sock);

char buf[BUF_SIZE];
char cwd_buf[CWD_SIZE];

int main(int argc, char **argv)
{
    int s;
    struct sockaddr_in host_channel;
    struct sockaddr_in client_channel;
    bzero(&host_channel,sizeof(host_channel));
    host_channel.sin_family = AF_INET;
    host_channel.sin_addr.s_addr = htons(INADDR_ANY);
    host_channel.sin_port = htons(SERVER_PORT);
    s = socket(PF_INET,SOCK_STREAM,0);
    if( s < 0)
    {
        printf("Can not create Socket!");
        exit(1);
    }
    else
        printf("Create a server successfully!\n");
    
    if( bind(s,(struct sockaddr*)&host_channel,sizeof(host_channel)))
    {
        printf("Can not bind port: %d!", SERVER_PORT); 
        exit(1);
    }

    if ( listen(s, QUEUE_SIZE) )
    {
        printf("Can not create listen!"); 
        exit(1);
    }

    char *orders,*chp,*words="&";
    char file_name[FILE_SIZE];
    socklen_t length = sizeof(client_channel);

    while (1) 
    {
        int new_sock = accept(s,(struct sockaddr*)&client_channel,&length);
	    if ( new_sock < 0)
        {
            printf("Server fail!\n");
            break;
       	}

        bzero(buf, BUF_SIZE);
	    length = recv(new_sock,buf,BUF_SIZE,0);
	    if (length < 0)
		{
            printf("Can not recieve data from client!\n");
           break;
		}
	    chp=buf;
        orders=strsep(&chp,words);
	    if(chp=strsep(&chp,words));
		    strcpy(file_name,chp);
	    if(strcmp(orders,"quit")==0)
		    quitser();
	    else if(strcmp(orders,"cd")==0)
		    cdser(file_name);
	    else if(strcmp(orders,"pwd")==0)
		    pwdser(new_sock);
	    else if(strcmp(orders,"dir")==0)
		    dirser(new_sock);
	    else if(strcmp(orders,"help")==0){}
	    else if(strcmp(orders,"get")==0&&*chp!='\0')
       	     getfile(new_sock,file_name);
	    else if(strcmp(orders,"put")==0&&*chp!='\0')
              sendfile(new_sock,file_name);
        close(new_sock);
    }
    close(s);
    return 0;
}

int getfile(int new_sock,char file_name[FILE_SIZE])
{
	int file_bl = 0;
	FILE * fp = fopen(file_name,"r");
	if(NULL == fp )
	{
	    	printf("'%s' is not found!\n", file_name);
	}
	else
	{
	   	bzero(buf, BUF_SIZE);
	   	while( (file_bl = fread(buf,sizeof(char),BUF_SIZE,fp))>0)
	        {
	        	if(send(new_sock,buf,file_bl,0)<0)
	        	{
	           		 printf("Can not send '%s' to client\n", file_name);
	           		 break;
	       		}
	        	bzero(buf, BUF_SIZE);
	    	}
           	fclose(fp);
           	printf("Send '%s' to client success!\n",file_name);
        }
	return 0;
}

int sendfile(int new_sock,char file_name[FILE_SIZE])
{
	int length;
	int write_length;
	bzero(buf,BUF_SIZE);
    	length = recv(new_sock,buf,BUF_SIZE,0);
    	if(length>0)
    	{
		FILE * fp = fopen(file_name,"w");    
    		if(NULL == fp )
    		{
        		printf("'%s' Can not open\n", file_name);
        		exit(1);
    		}
    		do{
        		if(length < 0)
        		{
            			printf("Can not recieve data from client!\n");
            			break;
        		}
        		write_length = fwrite(buf,sizeof(char),length,fp);
        		if (write_length<length)
        		{
            			printf("can not write '%s'\n", file_name);
            			break;
        		}
        		bzero(buf,BUF_SIZE);    
      	 	}while( length = recv(new_sock,buf,BUF_SIZE,0));
    		printf("Receive '%s' from client!\n",file_name); 
    		fclose(fp);
    	}
	return 0;
}

int pwdser(int new_sock)
{
	bzero(cwd_buf,CWD_SIZE);
	getcwd(cwd_buf,sizeof(cwd_buf));
	send( new_sock,cwd_buf,sizeof(cwd_buf),0);
	return 0;
}

int dirser(int new_sock)
{
	DIR *dirp;
	struct dirent *dirr;
	bzero(cwd_buf,CWD_SIZE);
	getcwd(cwd_buf,sizeof(cwd_buf));
	if((dirp=opendir(cwd_buf))==NULL)
		printf("Error in openning directory\n");
	else
	{
		bzero(buf,BUF_SIZE);
		while((dirr=readdir(dirp))!=NULL)
		{	
			strcpy(buf,dirr->d_name);
			if(send(new_sock,buf,BUF_SIZE,0)<0)
			{
				printf("Error in sending directory\n");
				break;
			}
			bzero(buf,BUF_SIZE);
		}
	}	
	return 0;
}

int cdser(char file_name[FILE_SIZE])
{
	chdir(file_name);
	return 0;
}

int quitser()
{
	printf("A client quit!\n");
	return 0;
}






