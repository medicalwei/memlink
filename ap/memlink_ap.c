#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "../linux/virtio_memlink.h"

// #define PAGES 1024*256 /* 1G */
#define PAGES 4
#define PAGESIZE 4096

int main(int argc, char *argv[])
{
	int fd;
	int *a = (int *) valloc(PAGESIZE*PAGES);
	int i;
	struct virtio_memlink_ioctl_input memlink_input;
	mlock(a, PAGESIZE*PAGES);

	if (argc < 2) {
		printf("Usage: prog \n");
		return -1;
	}

	fd = open(argv[1], O_RDWR);
	if (fd < 0) {
		perror("open failed");
		return -1;
	}

	for(i=0; i<PAGES; i++){
		a[i*PAGESIZE/4] = i;
		printf("%d ", a[i*PAGESIZE/sizeof(int)]);
	}

	printf("\n");

	memlink_input.gva = (long unsigned int) a;
	memlink_input.size = PAGESIZE*PAGES;

	if (ioctl(fd, MEMLINK_IOC_CREATE, &memlink_input) < 0) {
		printf("send ptr failed\n");
		return -1;
	}

	printf("created, id: %d\n", memlink_input.id);

	getchar();

	for(i=0; i<PAGES; i++){
		printf("%d ", a[i*PAGESIZE/sizeof(int)]);
	}
	printf("\n");

	getchar();

	if (ioctl(fd, MEMLINK_IOC_REVOKE, memlink_input.id) < 0) {
		printf("send ptr failed\n");
		return -1;
	}

	printf("revoked\n");

	for(i=0; i<PAGES; i++){
		printf("%d ", a[i*PAGESIZE/sizeof(int)]);
	}
	printf("\n");

	getchar();

	munlockall();

	return 0;
}
