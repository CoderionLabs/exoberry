/*
 * Copyright (c) 2013 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <compiler.h>
#include <debug.h>
#include <kernel/debug.h>
#include <kernel/thread.h>
#include <kernel/timer.h>
#include <kernel/mp.h>
#include <kernel/port.h>

void kernel_init(void)
{
    // if enabled, configure the kernel's event log
    kernel_evlog_init();

    // initialize the threading system
    dprintf(SPEW, "initializing mp\n");
    mp_init();

    // initialize the threading system
    dprintf(SPEW, "initializing threads\n");
    thread_init();

    // initialize kernel timers
    dprintf(SPEW, "initializing timers\n");
    timer_init();

    // initialize ports
    dprintf(SPEW, "initializing ports\n");
    port_init();
}

