/*
 * Copyright (c) 2015 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <trace.h>
#include <err.h>
#include <debug.h>
#include <arch/or1k.h>
#include <arch/ops.h>
#include <arch/mmu.h>

void arch_early_init(void)
{
}

void arch_init(void)
{
    TRACE;
}

void arch_idle(void)
{
}

void arch_chain_load(void *entry, ulong arg0, ulong arg1, ulong arg2, ulong arg3)
{
    PANIC_UNIMPLEMENTED;
}
