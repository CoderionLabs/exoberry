/*
 * Copyright (c) 2015 Eric Holland
 * Copyright 2018 The DEOS Authors
 */
#include <stdarg.h>
#include <reg.h>
#include <debug.h>
#include <stdio.h>
#include <assert.h>
#include <err.h>
#include <lib/cbuf.h>
#include <arch/arm/cm.h>
#include <arch/ops.h>
#include <dev/uart.h>
#include <dev/gpio.h>
#include <kernel/thread.h>
#include <platform/debug.h>
#include <platform/gpio.h>
#include <target/debugconfig.h>
#include <target/gpioconfig.h>

#define RXBUF_SIZE 16

cbuf_t uart0_rx_buf;



void uart_init_early(void)
{
#ifdef ENABLE_UART0

#ifdef  UART0_TX_PIN
    gpio_config(UART0_TX_PIN,GPIO_OUTPUT);
    NRF_UART0->PSELTXD =   UART0_TX_PIN;
#endif
#ifdef  UART0_RX_PIN
    gpio_config(UART0_RX_PIN,GPIO_INPUT);
    NRF_UART0->PSELRXD =   UART0_RX_PIN;
#endif

    NRF_UART0->BAUDRATE =   UART_BAUDRATE_BAUDRATE_Baud115200   <<  UART_BAUDRATE_BAUDRATE_Pos;
    NRF_UART0->CONFIG   =   UART_CONFIG_HWFC_Disabled << UART_CONFIG_HWFC_Pos | \
                            UART_CONFIG_PARITY_Excluded << UART_CONFIG_PARITY_Pos;
    NVIC_DisableIRQ(UARTE0_UART0_IRQn);
    NRF_UART0->ENABLE   =   UART_ENABLE_ENABLE_Enabled << UART_ENABLE_ENABLE_Pos;
    NRF_UART0->TXD = 'L';       //Must prime the tx queue with a character to start operation
    NRF_UART0->TASKS_STARTTX=1;
    NRF_UART0->TASKS_STARTRX=1;
#endif //ENABLE_UART0
}

void uart_init(void)
{
#ifdef ENABLE_UART0
    cbuf_initialize(&uart0_rx_buf, RXBUF_SIZE);
    NRF_UART0->INTENSET = UART_INTENSET_RXDRDY_Enabled << UART_INTENSET_RXDRDY_Pos;
    NRF_UART0->EVENTS_RXDRDY = 0;
    NVIC_EnableIRQ(UARTE0_UART0_IRQn);
    char c = NRF_UART0->RXD;
    (void)c;
#endif //ENABLE_UART0
}

void nrf52_UARTE0_UART0_IRQ(void)
{
    char c;
    arm_cm_irq_entry();

    bool resched = false;
    while ( NRF_UART0->EVENTS_RXDRDY > 0 ) {
        NRF_UART0->EVENTS_RXDRDY = 0;
        c = NRF_UART0->RXD;
        if (!cbuf_space_avail(&uart0_rx_buf)) {
            break;
        }
        cbuf_write_char(&uart0_rx_buf, c, false);
        resched = true;
    }

    arm_cm_irq_exit(resched);
}

int uart_putc(int port, char c)
{
    while (NRF_UART0->EVENTS_TXDRDY == 0);
    NRF_UART0->EVENTS_TXDRDY = 0;
    NRF_UART0->TXD = c;
    return 1;
}

int uart_getc(int port, bool wait)
{
    cbuf_t *rxbuf = &uart0_rx_buf;

    char c;
    if (cbuf_read_char(rxbuf, &c, wait) == 1)
        return c;

    return -1;
}

void uart_flush_tx(int port) {}

void uart_flush_rx(int port) {}

void uart_init_port(int port, uint baud)
{
    // TODO - later
    PANIC_UNIMPLEMENTED;
}
