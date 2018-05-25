/*
 * Copyright (c) 2013 Corey Tabaka
 * Copyright 2018 The DEOS Authors
 */

#include <err.h>
#include <dev/class/spi.h>

ssize_t class_spi_transaction(struct device *dev, struct spi_transaction *txn, size_t count)
{
    struct spi_ops *ops = device_get_driver_ops(dev, struct spi_ops, std);
    if (!ops)
        return ERR_NOT_CONFIGURED;

    if (ops->transaction)
        return ops->transaction(dev, txn, count);
    else
        return ERR_NOT_SUPPORTED;
}

