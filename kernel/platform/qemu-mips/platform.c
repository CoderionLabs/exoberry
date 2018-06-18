/*
 * Copyright (c) 2015 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <reg.h>
#include <sys/types.h>
#include <kernel/thread.h>
#include <platform.h>
#include <platform/interrupts.h>
#include <platform/debug.h>
#include <platform/timer.h>
#include <platform/qemu-mips.h>
#include <arch/mips.h>

extern void platform_init_interrupts(void);
extern void platform_init_uart(void);
extern void uart_init(void);

void platform_early_init(void)
{
    platform_init_interrupts();
    platform_init_uart();

    mips_init_timer(100000000);
    mips_enable_irq(2);
}

void platform_init(void)
{
    uart_init();
}

