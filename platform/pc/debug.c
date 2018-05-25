/*
 * Copyright (c) 2009 Corey Tabaka
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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

