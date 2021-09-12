#ifndef SPIN_LOCK_H
#define SPIN_LOCK_H

#include "printf.h"

typedef struct spinlock {
	volatile int lock;
} spinlock_t;

//TODO Enable SMP
//extern void spin_lock(spinlock_t *lock);
//extern void spin_unlock(spinlock_t *lock);

static inline void spind_lock(spinlock_t * lock)
{
	printf("LOCKED\n");
	lock->lock = 1;
}

static inline void spind_unlock(spinlock_t * lock)
{
	printf("UNLOCKED\n");
	lock->lock = 0;
}

#endif
