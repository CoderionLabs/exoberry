/*
 * Copyright (c) 2015 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <asm.h>

/* void x86_64_context_switch(uint64_t *oldsp, uint64_t newsp) */
FUNCTION(x86_64_context_switch)
    /* save the old context and restore the new */
    pushf
    pushq %rbx
    pushq %rbp
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15

    movq %rsp,(%rdi)
    movq %rsi,%rsp

    popq %r15
    popq %r14
    popq %r13
    popq %r12
    popq %rbp
    popq %rbx
    popf

    retq

