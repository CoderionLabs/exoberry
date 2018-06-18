/*
 * Copyright (c) 2008 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#ifndef __PLATFORM_INTERRUPTS_H
#define __PLATFORM_INTERRUPTS_H

#include <sys/types.h>

status_t mask_interrupt(unsigned int vector);
status_t unmask_interrupt(unsigned int vector);

typedef enum handler_return (*int_handler)(void *arg);

void register_int_handler(unsigned int vector, int_handler handler, void *arg);

#endif
