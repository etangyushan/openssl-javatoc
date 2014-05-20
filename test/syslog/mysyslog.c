#include <syslog.h>

int main(int argc, char **argv)
{
	openlog ("MyMsgMARK", LOG_CONS|LOG_PID, LOG_LOCAL0);
	syslog (LOG_EMERG, "This is a syslog test message generated by program '%s'/n", argv[0]);
	closelog();
	return 0;
}

