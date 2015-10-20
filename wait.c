#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>
#include "light.h"
#include <string.h>
#include <errno.h>


void sig_handler(int signo)
{
	printf("received signal!\n");
}

int main(int argc, char *argv[])
{
	int nr = 0;

	if (signal(SIGINT, sig_handler) == SIG_ERR)
		printf("Cannot catch signal\n");
	printf("waiting on %d\n", atoi(argv[1]));
	nr = syscall(381, atoi(argv[1]));
	printf("%d finished waiting\n", getpid());
	printf("%d %s\n", nr, strerror(errno));
	return 0;
}
