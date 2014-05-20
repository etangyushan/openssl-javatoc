#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>
#include <assert.h>
#include <stdio.h>

int my_syslog()
{
	int logfd, tempfd;
	logfd = open ("log.self", O_CREAT | O_RDWR | O_APPEND, 0664);
	assert (-1 != logfd);
	/* 保存标准错误的文件描述符 */
	dup2 (STDERR_FILENO, tempfd);
	/* 关闭标准文件描述 */
	close (STDERR_FILENO);
	/* 把自己创建的文件描述符付给标准出错 */
	dup2 (logfd, STDERR_FILENO);
	/* 关闭自己的文件描述符 */
	close (logfd);
	/*  */
	openlog ("syslog2", LOG_PERROR, LOG_DAEMON);
	syslog (LOG_DEBUG, "%i\n", time(NULL));
	/* 恢复标准出错 */
	dup2 (tempfd, STDERR_FILENO);
	/* 关闭临时文件描述符 */
	close (tempfd);
	closelog ();
	return 0;
}

int main()
{
	my_syslog();
	fprintf (stderr, "hello\n");
}
