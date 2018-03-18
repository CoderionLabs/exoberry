#ifndef DEOS_INC_SYSCALL_H
#define DEOS_INC_SYSCALL_H

/* system call numbers */
enum {
	SYS_cputs = 0,
	SYS_cgetc,
	SYS_getenvid,
	SYS_env_destroy,
	NSYSCALLS
};

#endif /* !DEOS_INC_SYSCALL_H */
