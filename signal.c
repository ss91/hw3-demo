#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "light.h"
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int nr = 0;
	int cur_int = 0;

	printf("signalling %d\n", atoi(argv[1]));
	cur_int = atoi(argv[1]);
	struct light_intensity temp;

	temp.cur_intensity = cur_int;

	nr = syscall(382, &temp);
	printf("%d\n", nr);
	printf("%s\n", strerror(errno));
	return 0;
}
