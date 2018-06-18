/*
 * Copyright (c) 2012 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <err.h>
#include <debug.h>
#include <target.h>
#include <compiler.h>
#include <dev/gpio.h>
#include <platform/gpio.h>
#include <platform/nrf51.h>
#include <target/gpioconfig.h>

void target_early_init(void)
{
    /* configure the usart1 pins */
    gpio_config(GPIO_LED1, GPIO_OUTPUT);
    gpio_config(GPIO_LED2, GPIO_OUTPUT);
    gpio_config(GPIO_LED3, GPIO_OUTPUT);
    gpio_config(GPIO_LED4, GPIO_OUTPUT);

    gpio_set(GPIO_LED1,1);
    gpio_set(GPIO_LED2,1);
    gpio_set(GPIO_LED3,0);
    gpio_set(GPIO_LED4,0);

    nrf51_debug_early_init();
}


void target_init(void)
{
    nrf51_debug_init();
    dprintf(SPEW,"Target: PCA10028 DK...\n");
}
