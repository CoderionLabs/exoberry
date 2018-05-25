/*
 * Copyright (c) 2012 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <debug.h>
#include <compiler.h>
#include <stdint.h>

/* externals */
extern unsigned int __data_start_rom, __data_start, __data_end;
extern unsigned int __bss_start, __bss_end;

extern void lk_main(void) __NO_RETURN __EXTERNALLY_VISIBLE;

void _start(void)
{
    /* copy data from rom */
    if (&__data_start != &__data_start_rom) {
        unsigned int *src = &__data_start_rom;
        unsigned int *dest = &__data_start;

        while (dest != &__data_end)
            *dest++ = *src++;
    }

    /* zero out bss */
    unsigned int *bss = &__bss_start;
    while (bss != &__bss_end)
        *bss++ = 0;

    lk_main();
}
