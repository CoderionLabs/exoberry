/*
 * Copyright (c) 2008-2014 Travis Geiselbrecht
 * Copyright (c) 2012 Shantanu Gupta
 * Copyright 2018 The DEOS Authors
 */
#ifndef __KERNEL_MUTEX_H
#define __KERNEL_MUTEX_H

#include <compiler.h>
#include <debug.h>
#include <stdint.h>
#include <kernel/thread.h>

__BEGIN_CDECLS;

#define MUTEX_MAGIC (0x6D757478)  // 'mutx'

typedef struct mutex {
    uint32_t magic;
    thread_t *holder;
    int count;
    wait_queue_t wait;
} mutex_t;

#define MUTEX_INITIAL_VALUE(m) \
{ \
    .magic = MUTEX_MAGIC, \
    .holder = NULL, \
    .count = 0, \
    .wait = WAIT_QUEUE_INITIAL_VALUE((m).wait), \
}

/* Rules for Mutexes:
 * - Mutexes are only safe to use from thread context.
 * - Mutexes are non-recursive.
*/

void mutex_init(mutex_t *);
void mutex_destroy(mutex_t *);
status_t mutex_acquire_timeout(mutex_t *, lk_time_t); /* try to acquire the mutex with a timeout value */
status_t mutex_release(mutex_t *);

static inline status_t mutex_acquire(mutex_t *m)
{
    return mutex_acquire_timeout(m, INFINITE_TIME);
}

/* does the current thread hold the mutex? */
static bool is_mutex_held(mutex_t *m)
{
    return m->holder == get_current_thread();
}

__END_CDECLS;
#endif

