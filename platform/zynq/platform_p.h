/*
 * Copyright (c) 2012 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#ifndef __PLATFORM_P_H
#define __PLATFORM_P_H

void platform_init_interrupts(void);
void platform_init_timer(uint32_t freq);
void zynq_gpio_init(void);

#endif

