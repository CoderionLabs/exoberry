/*
 * Copyright (c) 2015 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <compiler.h>
#include <trace.h>
#include <arch/microblaze.h>
#include <kernel/thread.h>

void microblaze_irq(void) __attribute__((interrupt_handler));

enum handler_return platform_irq_handler(void);

void microblaze_irq(void)
{
    if (platform_irq_handler() == INT_RESCHEDULE)
        thread_preempt();
}

