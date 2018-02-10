#define _GNU_SOURCE	// for Linux-specific F_SETSIG
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include "libfdhj.h"
#include "ceh.h"

int main(int argc, const char *argv[])
{
	if (argc < 5)
	{
		printf("Usage: %s <pid1> <fd1> <pid2> <fd2> [<pid3> <fd3>]\n",
			   argv[0]);
		return -1;
	} 
	int exit_code = 0;

	fdhj_open_dev();

	pid_t pid = atoi(argv[1]);
	int fd = atoi(argv[2]); 
    pid_t pid2 = atoi(argv[3]);
	int fd2 = atoi(argv[4]); 
    pid_t pid3;
    int fd3;
	if (argc > 6)
    {
        pid3 = atoi(argv[5]);
        fd3 = atoi(argv[6]);
    }

    if (!pid)
    {
        pid = getpid();
        fd = open("/dev/null", O_RDWR);
    }
    if (!pid2)
    {
        pid2 = getpid();
        fd2 = open("/dev/null", O_RDWR);
    }
    if (!pid3)
    {
        pid3 = getpid();
        fd3 = open("/dev/null", O_RDWR);
    }

	try
	{
        fdhj_exchange_fd(pid, fd, pid2, fd2);
        if (argc > 6)
            fdhj_exchange_fd(pid3, fd3, pid2, fd2);
	}
	catch
	{
		exit_code = pceherr(ceh_ex_info);
	}
	end_try

out1:
	fdhj_close_dev();

	return exit_code;
}
