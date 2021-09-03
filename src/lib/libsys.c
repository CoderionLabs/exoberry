#include "lib/libsys.h"


void libsys_write(char * buf)
{
	sys_write(buf);
}

int libsys_fork()
{
	return copy_process(0, 0, 0);
}

void libsys_exit()
{
	sys_exit();
}

void * const libsys_call_table[] = {libsys_write, libsys_fork, libsys_exit};
