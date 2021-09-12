#ifndef _SYS_H
#define _SYS_H

#define __NR_syscalls 2

#ifndef __ASSEMBLER__

#include <stdint.h>

//typedef unsigned int   uint32_t;
//typedef unsigned short uint16_t;
//typedef unsigned char  uint8_t;

void sys_write(char * buf);
void sys_exit();

#endif

#endif /*_SYS_H */
