/*
 * Copyright (c) 2012 Corey Tabaka
 * Copyright 2018 The DEOS Authors
 */

#include <dev/driver.h>
#include <assert.h>
#include <err.h>
#include <trace.h>

extern struct device __devices[];
extern struct device __devices_end[];

status_t device_init_all(void)
{
    status_t res = NO_ERROR;

    struct device *dev = __devices;
    while (dev != __devices_end) {
        status_t code = device_init(dev);

        if (code < 0) {
            TRACEF("Driver init failed for driver \"%s\", device \"%s\", reason %d\n",
                   dev->driver->type, dev->name, code);

            res = code;
        }

        dev++;
    }

    return res;
}

status_t device_fini_all(void)
{
    status_t res = NO_ERROR;

    struct device *dev = __devices;
    while (dev != __devices_end) {
        status_t code = device_fini(dev);

        if (code < 0) {
            TRACEF("Driver fini failed for driver \"%s\", device \"%s\", reason %d\n",
                   dev->driver->type, dev->name, code);

            res = code;
        }

        dev++;
    }

    return res;
}

status_t device_init(struct device *dev)
{
    if (!dev)
        return ERR_INVALID_ARGS;

    DEBUG_ASSERT(dev->driver);

    const struct driver_ops *ops = dev->driver->ops;

    if (ops && ops->init)
        return ops->init(dev);
    else
        return ERR_NOT_SUPPORTED;
}

status_t device_fini(struct device *dev)
{
    if (!dev)
        return ERR_INVALID_ARGS;

    DEBUG_ASSERT(dev->driver);

    const struct driver_ops *ops = dev->driver->ops;

    if (ops && ops->fini)
        return ops->fini(dev);
    else
        return ERR_NOT_SUPPORTED;
}

status_t device_suspend(struct device *dev)
{
    if (!dev)
        return ERR_NOT_SUPPORTED;

    DEBUG_ASSERT(dev->driver);

    const struct driver_ops *ops = dev->driver->ops;

    if (ops && ops->suspend)
        return ops->suspend(dev);
    else
        return ERR_NOT_SUPPORTED;
}

status_t device_resume(struct device *dev)
{
    if (!dev)
        return ERR_NOT_SUPPORTED;

    DEBUG_ASSERT(dev->driver);

    const struct driver_ops *ops = dev->driver->ops;

    if (ops && ops->resume)
        return ops->resume(dev);
    else
        return ERR_NOT_SUPPORTED;
}

