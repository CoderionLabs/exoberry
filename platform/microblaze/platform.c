/*
 * Copyright (c) 2015 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <reg.h>
#include <kernel/thread.h>
#include <platform.h>
#include <platform/interrupts.h>
#include <platform/debug.h>
#include <platform/timer.h>
#include <sys/types.h>
#include <target/microblaze-config.h>

void uartlite_putc(char c);
int uartlite_getc(bool wait);

void platform_dputc(char c)
{
    if (c == '\n')
        uartlite_putc('\r');
    uartlite_putc(c);
}

int platform_dgetc(char *c, bool wait)
{
    for (;;) {
        int ret = uartlite_getc(wait);
        if (ret >= 0) {
            *c = ret;
            return 0;
        }

        if (!wait)
            return -1;

        thread_yield();
    }
}


