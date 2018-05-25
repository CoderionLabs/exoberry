/*
 * Copyright (c) 2016 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <debug.h>
#include <err.h>
#include <compiler.h>
#include <stdio.h>
#include <platform.h>
#include <platform/debug.h>
#include <arch/ops.h>
#include <arch/arm/cm.h>

void platform_halt(platform_halt_action suggested_action,
                   platform_halt_reason reason)
{
#if ENABLE_PANIC_SHELL
    if (reason == HALT_REASON_SW_PANIC) {
        dprintf(ALWAYS, "CRASH: starting debug shell... (reason = %d)\n", reason);
        arch_disable_ints();
        panic_shell_start();
    }
#endif  // ENABLE_PANIC_SHELL

    switch (suggested_action) {
        default:
        case HALT_ACTION_SHUTDOWN:
        case HALT_ACTION_HALT:
            dprintf(ALWAYS, "HALT: spinning forever... (reason = %d)\n", reason);
            arch_disable_ints();
            for (;;)
                arch_idle();
            break;
        case HALT_ACTION_REBOOT:
            dprintf(INFO, "REBOOT\n");
            arch_disable_ints();
            for (;;) {
                NVIC_SystemReset();
            }
            break;
    }

    dprintf(ALWAYS, "HALT: spinning forever... (reason = %d)\n", reason);
    arch_disable_ints();
    for (;;);
}

