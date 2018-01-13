#ifndef DEOS_KERN_MONITOR_H
#define DEOS_KERN_MONITOR_H
#ifndef DEOS_KERNEL
# error "This is a DEOS kernel header; user programs should not #include it"
#endif

struct Trapframe;

// Activate the kernel monitor,
// optionally providing a trap frame indicating the current state
// (NULL if none).
void monitor(struct Trapframe *tf);

// Functions implementing monitor commands.
int mon_help(int argc, char **argv, struct Trapframe *tf);
int mon_kerninfo(int argc, char **argv, struct Trapframe *tf);
int mon_backtrace(int argc, char **argv, struct Trapframe *tf);

#endif	// !DEOS_KERN_MONITOR_H
