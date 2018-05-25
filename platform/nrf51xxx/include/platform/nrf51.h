/*
 * Copyright (c) 2015 Eric Holland
 * Copyright 2018 The DEOS Authors
 */
#ifndef __PLATFORM_NRF51_H
#define __PLATFORM_NRF51_H

#include <platform/nrf518xx.h>

void nrf51_debug_early_init(void);
void nrf51_debug_init(void);
void nrf51_timer_early_init(void);
void nrf51_timer_init(void);
void nrf51_gpio_early_init(void);
void nrf51_flash_nor_early_init(void);
void nrf51_flash_nor_init(void);

#endif

