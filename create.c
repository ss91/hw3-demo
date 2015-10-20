#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "light.h"
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	if (argc != 3) {

		printf("Usage: ./create <req_intensity> <frequency>\n");
		return 0;
	}

	struct event_requirements cur;

	cur.req_intensity = atoi(argv[1]);
	cur.frequency = atoi(argv[2]);

	int nr = 0;

	nr = syscall(380, &cur);
	if (nr < 0)
		printf("%s\n", strerror(errno));
	else
		printf("event %d created\n", nr);
	return 0;
}
