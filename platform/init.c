/*
 * Copyright (c) 2008 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <err.h>
#include <debug.h>
#include <platform.h>

/*
 * default implementations of these routines, if the platform code
 * chooses not to implement.
 */

__WEAK void platform_init_mmu_mappings(void)
{
}

__WEAK void platform_early_init(void)
{
}

__WEAK void platform_init(void)
{
}

__WEAK void platform_quiesce(void)
{
}

