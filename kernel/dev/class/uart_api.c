/*
 * Copyright (c) 2013 Corey Tabaka
 * Copyright 2018 The DEOS Authors
 */

#include <err.h>
#include <dev/class/uart.h>

ssize_t class_uart_read(struct device *dev, void *buf, size_t len)
{
    struct uart_ops *ops = device_get_driver_ops(dev, struct uart_ops, std);

    if (!ops)
        return ERR_NOT_CONFIGURED;

    if (ops->read)
        return ops->read(dev, buf, len);
    else
        return ERR_NOT_SUPPORTED;
}

ssize_t class_uart_write(struct device *dev, const void *buf, size_t len)
{
    struct uart_ops *ops = device_get_driver_ops(dev, struct uart_ops, std);

    if (!ops)
        return ERR_NOT_CONFIGURED;

    if (ops->write)
        return ops->write(dev, buf, len);
    else
        return ERR_NOT_SUPPORTED;
}

