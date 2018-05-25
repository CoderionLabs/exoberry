/*
 * Copyright (c) 2015 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <trace.h>
#include <debug.h>
#include <stdint.h>
#include <arch/microblaze.h>

#define LOCAL_TRACE 0

void arch_early_init(void)
{
    LTRACE;

    /* enable i/d cache */
    uint32_t val = mb_read_msr();
    val |= (1 << (31 - 26)) | (1 << (31 - 24));
    mb_write_msr(val);
}

void arch_init(void)
{
    LTRACE;
}

void arch_idle(void)
{
    asm volatile("sleep");
}

void arch_chain_load(void *entry, ulong arg0, ulong arg1, ulong arg2, ulong arg3)
{
    PANIC_UNIMPLEMENTED;
}

/* unimplemented cache operations */
void arch_disable_cache(uint flags) { PANIC_UNIMPLEMENTED; }
void arch_enable_cache(uint flags) { PANIC_UNIMPLEMENTED; }

void arch_clean_cache_range(addr_t start, size_t len) { PANIC_UNIMPLEMENTED; }
void arch_clean_invalidate_cache_range(addr_t start, size_t len) { PANIC_UNIMPLEMENTED; }
void arch_invalidate_cache_range(addr_t start, size_t len) { PANIC_UNIMPLEMENTED; }
void arch_sync_cache_range(addr_t start, size_t len) { PANIC_UNIMPLEMENTED; }
