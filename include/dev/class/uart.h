/*
 * Copyright (c) 2013 Corey Tabaka
 * Copyright 2018 The DEOS Authors
 */
#ifndef __DEV_CLASS_UART_H
#define __DEV_CLASS_UART_H

#include <dev/driver.h>

/* uart interface */
struct uart_ops {
    struct driver_ops std;

    ssize_t (*read)(struct device *dev, void *buf, size_t len);
    ssize_t (*write)(struct device *dev, const void *buf, size_t len);
};


ssize_t class_uart_read(struct device *dev, void *buf, size_t len);
ssize_t class_uart_write(struct device *dev, const void *buf, size_t len);

#endif

