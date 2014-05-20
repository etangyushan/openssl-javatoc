#include <stdio.h>

/*init socket */
int sockconnect (char *server, int port)
{
  SOCKET control_sock;
  struct hostent *hp;
  int sockfd = socket (AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr;
  memset (&addr, 0, sizeof(struct sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_port = htons (port);
  hp = gethostbyname (server);
  memcpy (&);
  //addr.sin_addr = inet_addr (server);
  /* 连接到服务器端 */
  int res = connect (sockfd, (struct sockaddr*)&addr, sizeof(addr));
  if (res == -1)
  {
	  perror("connect");
	  exit(-1);
  }
  char buf[1024] = {};
  /* 客户端接收服务器端的一些欢迎信息 */
  read(sockfd, buf, sizeof(buf));
  return sockfd;
}

int ftpconnect (int sockfd, char *username, char *password)
{
  char send_buf[1024] = {}; 
  char read_buf[1024] = {}; 
  /* 命令 ”USER username\r\n” */
  sprintf (send_buf, "USER %s\r\n", username);
  /*客户端发送用户名到服务器端 */
  write (sockfd, send_buf, strlen(send_buf));
  /* 客户端接收服务器的响应码和信息，
   * 正常为 ”331 User name okay, need password.” */
  read (sockfd, read_buf, sizeof(read_buf));
  /* 命令 ”PASS password\r\n” */
  sprintf (send_buf, "PASS %s\r\n", password);
  /* 客户端发送密码到服务器端 */
  write (sockfd, send_buf, strlen(send_buf));
  /* 客户端接收服务器的响应码和信息，
   * 正常为 ”230 User logged in, proceed.” */
  read (sockfd, read_buf, sizeof(read_buf));
  return 0;
}

/* bei dong mo shi  */
int ftpbei (sockfd)
{
  char send_buf[1024] = {}; 
  char read_buf[1024] = {}; 
  /* 命令 ”PASV\r\n” */
  sprintf (send_buf, "PASV\r\n");
  /* 客户端告诉服务器用被动模式 */
  write (sockfd, send_buf, strlen(send_buf));
  /*客户端接收服务器的响应码和新开的端口号，
   * * 正常为 ”227 Entering passive mode (<h1,h2,h3,h4,p1,p2>)” */
  read (sockfd, read_buf, sizeof(read_buf));

}

int main()
{

}


