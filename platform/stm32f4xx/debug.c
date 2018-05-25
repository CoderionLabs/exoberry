/*
 * Copyright (c) 2012 Travis Geiselbrecht
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
#include <debug.h>
#include <stdio.h>
#include <kernel/thread.h>
#include <platform/debug.h>
#include <arch/ops.h>
#include <dev/uart.h>
#include <target/debugconfig.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_usart.h>
#include <arch/arm/cm.h>

void stm32_debug_early_init(void)
{
    uart_init_early();
}

/* later in the init process */
void stm32_debug_init(void)
{
    uart_init();
}

#define ITM_STIM0   0xE0000000
#define ITM_TCR     0xE0000E80

void platform_dputc(char c)
{
    // if ITM is enabled, send character to STIM0
    if (readl(ITM_TCR) & 1) {
        while (!readl(ITM_STIM0)) ;
        writeb(c, ITM_STIM0);
    }

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

void __debugger_console_putc(char c);

#define DCRDR 0xE000EDF8

void _debugmonitor(void)
{
    u32 n;
    arm_cm_irq_entry();
    n = readl(DCRDR);
    if (n & 0x80000000) {
        switch (n >> 24) {
            case 0x80: // write to console
                __debugger_console_putc(n & 0xFF);
                n = 0;
                break;
            default:
                n = 0x01000000;
        }
        writel(n, DCRDR);
    }
    arm_cm_irq_exit(1);
}
