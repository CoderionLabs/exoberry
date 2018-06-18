/*
 * Copyright (c) 2008 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#ifndef __PLATFORM_P_H
#define __PLATFORM_P_H

void platform_init_interrupts(void);
void platform_init_timer(void);
void platform_init_blkdev(void);
void platform_init_display(void);

#endif

