#include "printf.h"
#include "utils.h"
#include "sched.h"
#include "mm.h"


void sys_write(char * buf)
{
	printf(buf);
}

void sys_exit()
{
	exit_process();
}

void * const sys_call_table[] = {sys_write, sys_exit};
