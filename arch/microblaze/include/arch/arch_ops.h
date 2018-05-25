/*
 * Copyright (c) 2015 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <compiler.h>

#define USE_MSRSET 1

static inline void arch_enable_ints(void)
{
    CF;
    uint32_t temp;
    __asm__ volatile(
#if USE_MSRSET
        "msrset %0, (1<<1)"
#else
        "mfs    %0, rmsr;"
        "ori    %0, %0, (1<<1);"
        "mts    rmsr, %0"
#endif
        : "=r" (temp));
}

static inline void arch_disable_ints(void)
{
    uint32_t temp;
    __asm__ volatile(
#if USE_MSRSET
        "msrclr %0, (1<<1)"
#else
        "mfs    %0, rmsr;"
        "andni  %0, %0, (1<<1);"
        "mts    rmsr, %0"
#endif
        : "=r" (temp));
    CF;
}

static inline bool arch_ints_disabled(void)
{
    uint32_t state;

    __asm__ volatile(
        "mfs    %0, rmsr;"
        : "=r" (state));

    return !(state & (1<<1));
}

static inline int atomic_add(volatile int *ptr, int val)
{
    return __atomic_fetch_add(ptr, val, __ATOMIC_RELAXED);
}

static inline int atomic_or(volatile int *ptr, int val)
{
    return __atomic_fetch_or(ptr, val, __ATOMIC_RELAXED);
}

static inline int atomic_and(volatile int *ptr, int val)
{
    return __atomic_fetch_and(ptr, val, __ATOMIC_RELAXED);
}

static inline int atomic_swap(volatile int *ptr, int val)
{
    return __atomic_exchange_n(ptr, val, __ATOMIC_RELAXED);
}

/* use a global pointer to store the current_thread */
extern struct thread *_current_thread;

static inline struct thread *get_current_thread(void)
{
    return _current_thread;
}

static inline void set_current_thread(struct thread *t)
{
    _current_thread = t;
}

static inline uint32_t arch_cycle_count(void) { return 0; }

static inline uint arch_curr_cpu_num(void)
{
    return 0;
}

