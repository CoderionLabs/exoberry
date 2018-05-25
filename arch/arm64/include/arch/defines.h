/*
 * Copyright (c) 2008 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#define SHIFT_4K        (12)
#define SHIFT_16K       (14)
#define SHIFT_64K       (16)

/* arm specific stuff */
#ifdef ARM64_LARGE_PAGESIZE_64K
#define PAGE_SIZE_SHIFT (SHIFT_64K)
#elif ARM64_LARGE_PAGESIZE_16K
#define PAGE_SIZE_SHIFT (SHIFT_16K)
#else
#define PAGE_SIZE_SHIFT (SHIFT_4K)
#endif
#define USER_PAGE_SIZE_SHIFT SHIFT_4K

#define PAGE_SIZE (1UL << PAGE_SIZE_SHIFT)
#define USER_PAGE_SIZE (1UL << USER_PAGE_SIZE_SHIFT)

#if ARM64_CPU_CORTEX_A53 || ARM64_CPU_CORTEX_A57 || ARM64_CPU_CORTEX_A72
#define CACHE_LINE 64
#else
#define CACHE_LINE 32
#endif
