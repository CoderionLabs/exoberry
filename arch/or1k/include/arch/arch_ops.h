/*
 * Copyright (c) 2015 Stefan Kristiansson
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <compiler.h>
#include <arch/or1k.h>

#ifndef ASSEMBLY
static inline void arch_enable_ints(void)
{
    uint32_t sr = mfspr(OR1K_SPR_SYS_SR_ADDR);

    sr |= OR1K_SPR_SYS_SR_IEE_MASK | OR1K_SPR_SYS_SR_TEE_MASK;
    mtspr(OR1K_SPR_SYS_SR_ADDR, sr);
}

static inline void arch_disable_ints(void)
{
    uint32_t sr = mfspr(OR1K_SPR_SYS_SR_ADDR);

    sr &= ~(OR1K_SPR_SYS_SR_IEE_MASK | OR1K_SPR_SYS_SR_TEE_MASK);
    mtspr(OR1K_SPR_SYS_SR_ADDR, sr);
}

static inline bool arch_ints_disabled(void)
{
    uint32_t sr = mfspr(OR1K_SPR_SYS_SR_ADDR);

    return !(sr & (OR1K_SPR_SYS_SR_IEE_MASK | OR1K_SPR_SYS_SR_TEE_MASK));
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

static inline int atomic_cmpxchg(volatile int *ptr, int oldval, int newval)
{
    __asm__ __volatile__(
        "1: l.lwa %0, 0(%1) \n"
        "   l.sfeq %0, %2   \n"
        "   l.bnf 1f        \n"
        "    l.nop          \n"
        "   l.swa 0(%1), %3 \n"
        "   l.bnf 1b        \n"
        "1:  l.nop          \n"
        : "=&r"(oldval)
        : "r"(ptr), "r"(oldval), "r"(newval)
        : "cc", "memory");

    return oldval;
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
#endif // !ASSEMBLY
