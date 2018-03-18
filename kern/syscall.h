#ifndef DEOS_KERN_SYSCALL_H
#define DEOS_KERN_SYSCALL_H
#ifndef DEOS_KERNEL
# error "This is a DEOS kernel header; user programs should not #include it"
#endif

#include <inc/syscall.h>

int32_t syscall(uint32_t num, uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5);

#endif /* !DEOS_KERN_SYSCALL_H */
