/*
 * Copyright (c) 2015 Brian Swetland
 * Copyright 2018 The DEOS Authors
 */

#include <reg.h>
#include <platform/lpc43xx-gpio.h>

inline int gpio_config(unsigned nr, unsigned flags)
{
    unsigned m = _GPIOm(nr);
    unsigned n = _GPIOn(nr);
    if (flags & GPIO_INPUT) {
        writel(readl(GPIO_DIR(m)) & (~(1 << n)), GPIO_DIR(m));
    } else {
        writel(readl(GPIO_DIR(m)) | (1 << n), GPIO_DIR(m));
    }
    return 0;
}

inline void gpio_set(unsigned nr, unsigned on)
{
    writel(on, GPIO_WORD(nr));
}

inline int gpio_get(unsigned nr)
{
    return readl(GPIO_WORD(nr)) & 1;
}
