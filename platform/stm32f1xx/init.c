/*
 * Copyright (c) 2012-2014 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <err.h>
#include <debug.h>
#include <dev/uart.h>
#include <platform.h>
#include <platform/stm32.h>
#include <arch/arm/cm.h>
#include <stm32f10x_rcc.h>
#include "system_stm32f10x.h"

void platform_early_init(void)
{
    // Crank up the clock before initing timers.
    SystemInit();

    // start the systick timer
    RCC_ClocksTypeDef clocks;
    RCC_GetClocksFreq(&clocks);
    arm_cm_systick_init(clocks.SYSCLK_Frequency);

    stm32_timer_early_init();
    stm32_gpio_early_init();
    stm32_flash_nor_early_init();
}

void platform_init(void)
{
    stm32_timer_init();
    stm32_flash_nor_init();
}
