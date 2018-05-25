/*
 * Copyright (c) 2008-2014 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#ifndef __ARCH_OPS_H
#define __ARCH_OPS_H

#ifndef ASSEMBLY

#include <sys/types.h>
#include <stddef.h>
#include <stdbool.h>
#include <compiler.h>

__BEGIN_CDECLS

/* fast routines that most arches will implement inline */
static void arch_enable_ints(void);
static void arch_disable_ints(void);
static bool arch_ints_disabled(void);
static bool arch_in_int_handler(void);

static int atomic_swap(volatile int *ptr, int val);
static int atomic_add(volatile int *ptr, int val);
static int atomic_and(volatile int *ptr, int val);
static int atomic_or(volatile int *ptr, int val);

static uint32_t arch_cycle_count(void);

static uint arch_curr_cpu_num(void);

/* Use to align structures on cache lines to avoid cpu aliasing. */
#define __CPU_ALIGN __ALIGNED(CACHE_LINE)

#endif // !ASSEMBLY
#define ICACHE 1
#define DCACHE 2
#define UCACHE (ICACHE|DCACHE)
#ifndef ASSEMBLY

void arch_disable_cache(uint flags);
void arch_enable_cache(uint flags);

void arch_clean_cache_range(addr_t start, size_t len);
void arch_clean_invalidate_cache_range(addr_t start, size_t len);
void arch_invalidate_cache_range(addr_t start, size_t len);
void arch_sync_cache_range(addr_t start, size_t len);

void arch_idle(void);

__END_CDECLS

#endif // !ASSEMBLY

#include <arch/arch_ops.h>

#endif
