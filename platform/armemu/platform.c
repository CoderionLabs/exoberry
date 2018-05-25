/*
 * Copyright (c) 2008 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <err.h>
#include <debug.h>
#include <platform.h>
#include "platform_p.h"

void platform_init_mmu_mappings(void)
{
}

void platform_early_init(void)
{
    /* initialize the interrupt controller */
    platform_init_interrupts();

    /* initialize the timer block */
    platform_init_timer();

    /* initialize the display */
    platform_init_display();
}

void platform_init(void)
{
    platform_init_blkdev();
}

