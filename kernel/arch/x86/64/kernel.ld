/*
 * Copyright (c) 2009 Corey Tabaka
 * Copyright (c) 2013 Travis Geiselbrecht
 * Copyright (c) 2015 Intel Corporation
 * Copyright 2018 The DEOS Authors
 */

ENTRY(_start)
SECTIONS
{
    . = %KERNEL_BASE% + %KERNEL_LOAD_OFFSET%;

    .text : AT(%MEMBASE% + %KERNEL_LOAD_OFFSET%) {
        __code_start = .;
        KEEP(*(.text.boot))
        *(.text* .sram.text)
        *(.gnu.linkonce.t.*)
        __code_end = .;
    } =0x9090

    .rodata : ALIGN(4096) {
        __rodata_start = .;
        *(.rodata*)
        *(.gnu.linkonce.r.*)
        . = ALIGN(8);
    }

    /*
     * extra linker scripts tend to insert sections just after .rodata,
     * so we want to make sure this symbol comes after anything inserted above,
     * but not aligned to the next section necessarily.
     */
    .dummy_post_rodata : {
        __rodata_end = .;
    }

    .data : ALIGN(4096) {
        __data_start = .;
        *(.data .data.* .gnu.linkonce.d.*)
    }

    .ctors : ALIGN(4) {
        __ctor_list = .;
        KEEP(*(.ctors .init_array))
        __ctor_end = .;
    }
    .dtors : ALIGN(4) {
        __dtor_list = .;
        KEEP(*(.dtors .fini_array))
        __dtor_end = .;
    }

    .stab   : { *(.stab) }
    .stabst : { *(.stabstr) }

    /*
     * extra linker scripts tend to insert sections just after .data,
     * so we want to make sure this symbol comes after anything inserted above,
     * but not aligned to the next section necessarily.
     */
    .dummy_post_data : {
        __data_end = .;
    }

    .bss : ALIGN(4096) {
        __bss_start = .;
        *(.bss*)
        *(.gnu.linkonce.b.*)
        *(COMMON)
        . = ALIGN(8);
        __bss_end = .;
    }

    _end = .;

    /* put a symbol arbitrarily 4MB past the end of the kernel */
    /* used by the heap and other early boot time allocators */
    _end_of_ram = . + (4*1024*1024);

    /DISCARD/ : { *(.comment .note .eh_frame) }
}
