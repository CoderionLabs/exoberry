/*
 * Copyright (c) 2012 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <err.h>
#include <debug.h>
#include <trace.h>
#include <target.h>
#include <compiler.h>
#include <dev/gpio.h>
#include <stm32f2xx_usart.h>
#include <stm32f2xx_rcc.h>
#include <stm32f2xx_gpio.h>
#include <platform/stm32.h>
#include <platform/gpio.h>
#include <target/gpioconfig.h>

void target_early_init(void)
{
    /* configure the usart3 pins */
    gpio_config(GPIO_USART3_TX, GPIO_STM32_AF | GPIO_STM32_AFn(GPIO_AF_USART3) | GPIO_PULLUP);
    gpio_config(GPIO_USART3_RX, GPIO_STM32_AF | GPIO_STM32_AFn(GPIO_AF_USART3) | GPIO_PULLUP);

    stm32_debug_early_init();

    /* configure some status leds */
    gpio_config(GPIO_LED0, GPIO_OUTPUT);
    gpio_config(GPIO_LED1, GPIO_OUTPUT);
    gpio_config(GPIO_LED2, GPIO_OUTPUT);
    gpio_config(GPIO_LED3, GPIO_OUTPUT);
}

void target_init(void)
{
    TRACE_ENTRY;

    stm32_debug_init();

    TRACE_EXIT;
}

void target_set_debug_led(unsigned int led, bool on)
{
    switch (led) {
        case 0:
            gpio_set(GPIO_LED0, on);
            break;
        case 1:
            gpio_set(GPIO_LED1, on);
            break;
        case 2:
            gpio_set(GPIO_LED2, on);
            break;
        case 3:
            gpio_set(GPIO_LED3, on);
            break;
    }
}

