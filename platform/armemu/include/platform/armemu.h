/*
 * Copyright (c) 2008 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#ifndef __PLATFORM_ARMEMU_H
#define __PLATFORM_ARMEMU_H

#include <platform/armemu/memmap.h>

void debug_dump_regs(void);

void debug_dump_memory_bytes(void *mem, int len);
void debug_dump_memory_halfwords(void *mem, int len);
void debug_dump_memory_words(void *mem, int len);

void debug_set_trace_level(int trace_type, int level);

#endif

