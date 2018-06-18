/*
 * Copyright (c) 2009 Corey Tabaka
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <lib/cbuf.h>

extern cbuf_t console_input_buf;

void platform_init_debug_early(void);
void platform_init_debug(void);
void platform_init_interrupts(void);
void platform_init_timer(void);

