#ifndef _SYS_H
#define _SYS_H

#define __NR_syscalls 2

#ifndef __ASSEMBLER__

void sys_write(char * buf);
void sys_exit();

#endif

#endif /*_SYS_H */
