/*
 * Copyright (c) 2012 Google, Inc.
 * Copyright 2018 The DEOS Authors
 */
#include <debug.h>
#include <err.h>
#include <compiler.h>
#include <platform.h>
#include <platform/debug.h>
#include <kernel/thread.h>
#include <stdio.h>
#include <lib/console.h>

/*
 * default implementations of these routines, if the platform code
 * chooses not to implement.
 */
__WEAK void platform_halt(platform_halt_action suggested_action,
                          platform_halt_reason reason)
{
#if ENABLE_PANIC_SHELL

    if (reason == HALT_REASON_SW_PANIC) {
        dprintf(ALWAYS, "CRASH: starting debug shell... (reason = %d)\n", reason);
        arch_disable_ints();
        panic_shell_start();
    }

#endif  // ENABLE_PANIC_SHELL

    dprintf(ALWAYS, "HALT: spinning forever... (reason = %d)\n", reason);
    arch_disable_ints();
    for (;;);
}

#if WITH_LIB_CONSOLE

#include <lib/console.h>

static int cmd_reboot(int argc, const cmd_args *argv)
{
    platform_halt(HALT_ACTION_REBOOT, HALT_REASON_SW_RESET);
    return 0;
}

static int cmd_poweroff(int argc, const cmd_args *argv)
{
    platform_halt(HALT_ACTION_SHUTDOWN, HALT_REASON_SW_RESET);
    return 0;
}

STATIC_COMMAND_START
#if LK_DEBUGLEVEL > 1
STATIC_COMMAND("reboot", "soft reset", &cmd_reboot)
STATIC_COMMAND("poweroff", "powerdown", &cmd_poweroff)
#endif
STATIC_COMMAND_END(platform_power);

#endif
