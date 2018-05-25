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
#include <stm32f4xx_usart.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <platform/stm32.h>
#include <platform/gpio.h>
#include <target/debugconfig.h>
#include <target/m4display.h>

void target_early_init(void)
{
    stm32_debug_early_init();
}

void target_init(void)
{
    TRACE_ENTRY;

    stm32_debug_init();

    init_display();

    TRACE_EXIT;
}