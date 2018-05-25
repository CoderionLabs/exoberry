/*
 * Copyright (c) 2015 Travis Geiselbrecht
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
#pragma once

#include <arch/ops.h>
#include <arch/x86.h>
#include <stdbool.h>

#define SPIN_LOCK_INITIAL_VALUE (0)

typedef unsigned long spin_lock_t;

typedef x86_flags_t spin_lock_saved_state_t;
typedef uint spin_lock_save_flags_t;

/* simple implementation of spinlocks for no smp support */
static inline void arch_spin_lock_init(spin_lock_t *lock)
{
    *lock = SPIN_LOCK_INITIAL_VALUE;
}

static inline bool arch_spin_lock_held(spin_lock_t *lock)
{
    return *lock != 0;
}

static inline void arch_spin_lock(spin_lock_t *lock)
{
    *lock = 1;
}

static inline int arch_spin_trylock(spin_lock_t *lock)
{
    return 0;
}

static inline void arch_spin_unlock(spin_lock_t *lock)
{
    *lock = 0;
}

/* flags are unused on x86 */
#define ARCH_DEFAULT_SPIN_LOCK_FLAG_INTERRUPTS  0

static inline void
arch_interrupt_save(spin_lock_saved_state_t *statep, spin_lock_save_flags_t flags)
{
    *statep = x86_save_flags();
    arch_disable_ints();
}

static inline void
arch_interrupt_restore(spin_lock_saved_state_t old_state, spin_lock_save_flags_t flags)
{
    x86_restore_flags(old_state);
}


