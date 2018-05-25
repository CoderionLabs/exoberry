/*
 * Copyright (c) 2008-2014 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <stdarg.h>
#include <reg.h>
#include <stdio.h>
#include <kernel/thread.h>
#include <dev/uart.h>
#include <platform/debug.h>
#include <platform/qemu-virt.h>
#include <target/debugconfig.h>
#include <reg.h>

/* DEBUG_UART must be defined to 0 or 1 */
#if defined(DEBUG_UART) && DEBUG_UART == 0
#define DEBUG_UART_BASE UART0_BASE
#elif defined(DEBUG_UART) && DEBUG_UART == 1
#define DEBUG_UART_BASE UART1_BASE
#else
#error define DEBUG_UART to something valid
#endif

void platform_dputc(char c)
{
    if (c == '\n')
        uart_putc(DEBUG_UART, '\r');
    uart_putc(DEBUG_UART, c);
}

int platform_dgetc(char *c, bool wait)
{
    int ret = uart_getc(DEBUG_UART, wait);
    if (ret == -1)
        return -1;
    *c = ret;
    return 0;
}

void platform_pputc(char c)
{
    if (c == '\n')
        uart_pputc(DEBUG_UART, '\r');
    uart_pputc(DEBUG_UART, c);
}

int platform_pgetc(char *c, bool wait)
{
    int ret = uart_pgetc(DEBUG_UART);
    if (ret < 0)
        return ret;
    *c = ret;
    return 0;
}

