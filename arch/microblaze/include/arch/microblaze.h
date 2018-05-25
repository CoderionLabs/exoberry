/*
 * Copyright (c) 2015 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#pragma once

static inline uint32_t mb_read_msr(void)
{
    uint32_t temp;
    __asm__ volatile(
        "mfs    %0, rmsr;" : "=r" (temp));

    return temp;
}

static inline void mb_write_msr(uint32_t val)
{
    __asm__ volatile(
        "mts    rmsr, %0" :: "r" (val));
}


