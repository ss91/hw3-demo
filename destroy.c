#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "light.h"

int main(int argc, char *argv[])
{
	int nr = 0;

	printf("waiting on %d\n", atoi(argv[1]));
	nr = syscall(383, atoi(argv[1]));
	printf("%d\n", nr);
	return 0;
}
