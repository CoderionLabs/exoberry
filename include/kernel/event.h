/*
 * Copyright (c) 2008-2014 Travis Geiselbrecht
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef __KERNEL_EVENT_H
#define __KERNEL_EVENT_H

#include <compiler.h>
#include <stdbool.h>
#include <sys/types.h>
#include <kernel/thread.h>

__BEGIN_CDECLS;

#define EVENT_MAGIC (0x65766E74)  // "evnt"

typedef struct event {
    int magic;
    bool signaled;
    uint flags;
    wait_queue_t wait;
} event_t;

#define EVENT_FLAG_AUTOUNSIGNAL 1

#define EVENT_INITIAL_VALUE(e, initial, _flags) \
{ \
    .magic = EVENT_MAGIC, \
    .signaled = initial, \
    .flags = _flags, \
    .wait = WAIT_QUEUE_INITIAL_VALUE((e).wait), \
}

/* Rules for Events:
 * - Events may be signaled from interrupt context *but* the reschedule
 *   parameter must be false in that case.
 * - Events may not be waited upon from interrupt context.
 * - Events without FLAG_AUTOUNSIGNAL:
 *   - Wake up any waiting threads when signaled.
 *   - Continue to do so (no threads will wait) until unsignaled.
 * - Events with FLAG_AUTOUNSIGNAL:
 *   - If one or more threads are waiting when signaled, one thread will
 *     be woken up and return.  The signaled state will not be set.
 *   - If no threads are waiting when signaled, the Event will remain
 *     in the signaled state until a thread attempts to wait (at which
 *     time it will unsignal atomicly and return immediately) or
 *     event_unsignal() is called.
*/

void event_init(event_t *, bool initial, uint flags);
void event_destroy(event_t *);
status_t event_wait_timeout(event_t *, lk_time_t); /* wait on the event with a timeout */
status_t event_signal(event_t *, bool reschedule);
status_t event_unsignal(event_t *);

static inline bool event_initialized(event_t *e)
{
    return e->magic == EVENT_MAGIC;
}

static inline status_t event_wait(event_t *e)
{
    return event_wait_timeout(e, INFINITE_TIME);
}

__END_CDECLS;

#endif

