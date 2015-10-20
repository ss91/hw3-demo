#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include "light.h"

#define __NR_set_light_intensity 378
#define __NR_get_light_intensity 379
#define __NR_light_evt_create 380
#define __NR_light_evt_wait 381
#define __NR_light_evt_signal 382
#define __NR_light_evt_destroy 383

int event_ids[3];

struct event_requirements event1 = {

	.req_intensity = 1000, /*Low intensity event*/
	.frequency = 20
};

struct event_requirements event2 = {

	.req_intensity = 10000, /*Medium intensity event*/
	.frequency = 20
};

struct event_requirements event3 = {

	.req_intensity = 50000, /*High intensity event */
	.frequency = 20
};

int do_create_event(void)
{

	int id = 0;
	int i = 0;

	id = syscall(__NR_light_evt_create, &event1);
	if (id <= 0)
		printf("EVENT CREATE FAIL\n");
	else
		event_ids[i++] = id;

	id = syscall(__NR_light_evt_create, &event2);
	if (id <= 0)
		printf("EVENT CREATE FAIL\n");
	else
		event_ids[i++] = id;

	id = syscall(__NR_light_evt_create, &event2);
	if (id <= 0)
		printf("EVENT CREATE FAIL\n");
	else
		event_ids[i++] = id;

	return i;
}

int do_wait_event(int i)
{

	int r = 0;
	int idx = i%3;

	printf("PROCESS %d waiting on EVENT %d\n", i, event_ids[idx]);
	r = syscall(__NR_light_evt_wait, event_ids[idx]);
	if (r < 0) {

		printf("%s\n", strerror(errno));
		printf("WAITING FAILED\n");
		return r;
	}

	if (idx == 0)
		printf("%d detected low intensity event\n", i);
	if (idx == 1)
		printf("%d detected medium intensity event\n", i);
	if (idx == 2)
		printf("%d detected high intensity event\n", i);

	return r;
}

void do_event_destroy(int n)
{
	int i = 0;
	int ret = 0;

	for (i = 0; i < n; i++) {
		ret = syscall(__NR_light_evt_destroy, event_ids[i]);
		printf("DESTROY EVENT %d returns %d\n", event_ids[i], ret);
	}
}


int main(int argc, char * const argv[])
{
	/* Write your test program here */
	int evt_n;
	int child_n;
	int idx = 0;
	int pid = 1;

	if (argc < 2) {
		printf("ARGUMENT MISSING\n");
		return 0;
	}

	child_n = atoi(argv[1]);
	evt_n = do_create_event();

	if (evt_n != 3) {
		printf("EVENT CREATE FAIL\n");
		return 0;
	}

	while (idx++, child_n != 0) {

		pid = fork();
		if (pid <= 0)
			break;

		child_n--;


	}

	if (pid < 0) {
		printf("FORK FAILED\n");
		return 0;
	}

	else if (pid == 0) {
		printf("%d beginning to wait\n", getpid());
		printf("wait return %d\n", do_wait_event(idx));
		return 0;
	}

	sleep(60);
	do_event_destroy(evt_n);
	return 0;
}
