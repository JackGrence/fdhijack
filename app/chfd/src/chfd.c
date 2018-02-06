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
		printf("Usage: %s <pid> <fd> <file path> [keep mode: 0 | 1]\n"
			   "       keep mode: do not exit after change fds, this can provide the opportunity\n"
			   "                  to change back the fd afterward\n",
			   argv[0]);
		return -1;
	} 
	int exit_code = 0;

	fdhj_open_dev();

	pid_t pid = atoi(argv[1]);
	int fd = atoi(argv[2]); 
    pid_t pid2 = atoi(argv[3]);
	int fd2 = atoi(argv[4]); 
	int keep = 0;
	if (argc > 5)
		keep = atoi(argv[5]);
	if (keep)
		printf("Keep mode = 1, just press enter to exchange the fd again.\n"
			   "Enter \"exit\" to exit\n");
	char buf[sizeof("exit")];
	char *ret;

	try
	{
		do {
			fdhj_exchange_fd(pid, fd, pid2, fd2);
			if (keep)
				ret = fgets(buf, sizeof(buf), stdin);
		} while (keep && ret && strcmp(ret, "exit"));
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
