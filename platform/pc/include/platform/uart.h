/*
 * Copyright (c) 2012 Corey Tabaka
 * Copyright 2018 The DEOS Authors
 */

#ifndef __PLATFORM_UART_H
#define __PLATFORM_UART_H

struct platform_uart_config {
    int baud_rate;
    int io_port;
    int irq;
    int rx_buf_len;
    int tx_buf_len;
};

#endif

