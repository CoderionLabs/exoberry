#ifndef SPIN_LOCK_H
#define SPIN_LOCK_H

typedef struct spinlock {
	volatile int lock;
} spinlock_t;

void spin_lock(spinlock_t *lock);
void spin_unlock(spinlock_t *lock);

#endif
