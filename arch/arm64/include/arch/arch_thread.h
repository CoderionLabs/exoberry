/*
 * Copyright (c) 2014 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <sys/types.h>

struct fpstate {
    uint64_t    regs[64];
    uint32_t    fpcr;
    uint32_t    fpsr;
    uint        current_cpu;
};

struct arch_thread {
    vaddr_t sp;
    struct fpstate fpstate;
};

