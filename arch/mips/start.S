/*
 * Copyright (c) 2015 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <asm.h>

.section ".text.boot"
FUNCTION(_start)
    # set the default stack
    la      $sp, default_stack_top

    # zero out the bss section
    la      $t0, __bss_start
    la     $t1, __bss_end
0:
    sw      $zero, ($t0)
    addi    $t0, 4
    bne     $t0, $t1, 0b

    # args to main and call it
    li      $a0, 1
    li      $a1, 2
    li      $a2, 3
    li      $a3, 4
    jal     lk_main

    # should never return here
    b       .

.bss
.align 3
LOCAL_DATA(default_stack)
    .skip 4096
LOCAL_DATA(default_stack_top)

