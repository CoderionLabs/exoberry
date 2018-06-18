/*
 * Copyright (c) 2009 Corey Tabaka
 * Copyright (c) 2015 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <stdarg.h>
#include <reg.h>
#include <trace.h>
#include <stdio.h>
#include <kernel/thread.h>
#include <lib/cbuf.h>
#include <platform/interrupts.h>
#include <platform/qemu-mips.h>

static int uart_baud_rate = 115200;
static int uart_io_port = 0x3f8;

static cbuf_t uart_rx_buf;

static enum handler_return uart_irq_handler(void *arg)
{
    unsigned char c;
    bool resched = false;

    while (isa_read_8(uart_io_port + 5) & (1<<0)) {
        c = isa_read_8(uart_io_port + 0);
        cbuf_write_char(&uart_rx_buf, c, false);
        resched = true;
    }

    return resched ? INT_RESCHEDULE : INT_NO_RESCHEDULE;
}

void platform_init_uart(void)
{
    /* configure the uart */
    int divisor = 115200 / uart_baud_rate;

    /* get basic config done so that tx functions */
    isa_write_8(uart_io_port + 3, 0x80); // set up to load divisor latch
    isa_write_8(uart_io_port + 0, divisor & 0xff); // lsb
    isa_write_8(uart_io_port + 1, divisor >> 8); // msb
    isa_write_8(uart_io_port + 3, 3); // 8N1
    isa_write_8(uart_io_port + 2, 0x07); // enable FIFO, clear, 14-byte threshold
}

void uart_init(void)
{
    /* finish uart init to get rx going */
    cbuf_initialize(&uart_rx_buf, 16);

    register_int_handler(0x4, uart_irq_handler, NULL);
    unmask_interrupt(0x4);

    isa_write_8(uart_io_port + 1, 0x1); // enable receive data available interrupt
}

void uart_putc(char c)
{
    while ((isa_read_8(uart_io_port + 5) & (1<<6)) == 0)
        ;
    isa_write_8(uart_io_port + 0, c);
}

int uart_getc(char *c, bool wait)
{
    return cbuf_read_char(&uart_rx_buf, c, wait);
}

void platform_dputc(char c)
{
    if (c == '\n')
        platform_dputc('\r');
#if WITH_CGA_CONSOLE
    cputc(c);
#else
    uart_putc(c);
#endif
}

int platform_dgetc(char *c, bool wait)
{
#if WITH_CGA_CONSOLE
    int ret =  platform_read_key(c);
    //if (ret < 0)
    //  arch_idle();
#else
    int ret = uart_getc(c, wait);
#endif

    return ret;
}
