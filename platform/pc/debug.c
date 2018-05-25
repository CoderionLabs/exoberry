/*
 * Copyright (c) 2009 Corey Tabaka
 * Copyright 2018 The DEOS Authors
 */
#include <stdarg.h>
#include <reg.h>
#include <stdio.h>
#include <kernel/thread.h>
#include <arch/x86.h>
#include <lib/cbuf.h>
#include <platform/interrupts.h>
#include <platform/pc/memmap.h>
#include <platform/console.h>
#include <platform/keyboard.h>
#include <platform/debug.h>

static const int uart_baud_rate = 115200;
static const int uart_io_port = 0x3f8;

cbuf_t console_input_buf;

static enum handler_return uart_irq_handler(void *arg)
{
    unsigned char c;
    bool resched = false;

    while (inp(uart_io_port + 5) & (1<<0)) {
        c = inp(uart_io_port + 0);
        cbuf_write_char(&console_input_buf, c, false);
        resched = true;
    }

    return resched ? INT_RESCHEDULE : INT_NO_RESCHEDULE;
}

void platform_init_debug_early(void)
{
    /* configure the uart */
    int divisor = 115200 / uart_baud_rate;

    /* get basic config done so that tx functions */
    outp(uart_io_port + 3, 0x80); // set up to load divisor latch
    outp(uart_io_port + 0, divisor & 0xff); // lsb
    outp(uart_io_port + 1, divisor >> 8); // msb
    outp(uart_io_port + 3, 3); // 8N1
    outp(uart_io_port + 2, 0x07); // enable FIFO, clear, 14-byte threshold
}

void platform_init_debug(void)
{
    /* finish uart init to get rx going */
    cbuf_initialize(&console_input_buf, 1024);

    register_int_handler(0x24, uart_irq_handler, NULL);
    unmask_interrupt(0x24);

    outp(uart_io_port + 1, 0x1); // enable receive data available interrupt
}

static void debug_uart_putc(char c)
{
    while ((inp(uart_io_port + 5) & (1<<6)) == 0)
        ;
    outp(uart_io_port + 0, c);
}

void platform_dputc(char c)
{
    if (c == '\n')
        platform_dputc('\r');

    cputc(c);
    debug_uart_putc(c);
}

int platform_dgetc(char *c, bool wait)
{
    return cbuf_read_char(&console_input_buf, c, wait);
}

void platform_halt(void)
{
    for (;;) {
        x86_cli();
        x86_hlt();
    }
}

