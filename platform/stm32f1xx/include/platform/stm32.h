/*
 * Copyright (c) 2012 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#ifndef __PLATFORM_STM32_H
#define __PLATFORM_STM32_H

void stm32_debug_early_init(void);
void stm32_debug_init(void);
void stm32_timer_early_init(void);
void stm32_timer_init(void);
void stm32_gpio_early_init(void);
void stm32_flash_nor_early_init(void);
void stm32_flash_nor_init(void);

#endif

