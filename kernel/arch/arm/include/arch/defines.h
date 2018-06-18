/*
 * Copyright (c) 2008 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#ifndef __ARCH_CPU_H
#define __ARCH_CPU_H

/* arm specific stuff */
#define PAGE_SIZE 4096
#define PAGE_SIZE_SHIFT 12

#if ARM_CPU_ARM7
/* irrelevant, no consistent cache */
#define CACHE_LINE 32
#elif ARM_CPU_ARM926
#define CACHE_LINE 32
#elif ARM_CPU_ARM1136
#define CACHE_LINE 32
#elif ARM_CPU_ARMEMU
#define CACHE_LINE 32
#elif ARM_CPU_CORTEX_A7
#define CACHE_LINE 64 /* XXX L1 icache is 32 bytes */
#elif ARM_CPU_CORTEX_A8
#define CACHE_LINE 64
#elif ARM_CPU_CORTEX_A9
#define CACHE_LINE 32
#elif ARM_CPU_CORTEX_M0 || ARM_CPU_CORTEX_M0_PLUS || ARM_CPU_CORTEX_M3 || ARM_CPU_CORTEX_M4
#define CACHE_LINE 32 /* doesn't actually matter */
#elif ARM_CPU_CORTEX_M7
#define CACHE_LINE 32
#elif ARM_CPU_CORTEX_A15
#define CACHE_LINE 64
#else
#error unknown cpu
#endif

#endif

