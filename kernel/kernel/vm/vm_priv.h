/*
 * Copyright (c) 2014 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <stdint.h>
#include <sys/types.h>
#include <kernel/vm.h>

/* simple boot time allocator */
void *boot_alloc_mem(size_t len) __MALLOC;
extern uintptr_t boot_alloc_start;
extern uintptr_t boot_alloc_end;

void vmm_init_preheap(void);
void vmm_init(void);

