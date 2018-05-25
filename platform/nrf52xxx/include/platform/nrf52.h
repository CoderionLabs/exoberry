/*
 * Copyright (c) 2016 Eric Holland
 * Copyright 2018 The DEOS Authors
 */
#ifndef __PLATFORM_NRF52_H
#define __PLATFORM_NRF52_H

#include <platform/nrf52xxx.h>

void nrf52_debug_early_init(void);
void nrf52_debug_init(void);
void nrf52_timer_early_init(void);
void nrf52_timer_init(void);
void nrf52_gpio_early_init(void);
void nrf52_flash_nor_early_init(void);
void nrf52_flash_nor_init(void);

#endif

