/*
 * Copyright (c) 2009 Corey Tabaka
 * Copyright (c) 2015 Intel Corporation
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <sys/types.h>

struct arch_thread {
    vaddr_t sp;
#if X86_WITH_FPU
    vaddr_t *fpu_states;
    uint8_t fpu_buffer[512 + 16];
#endif
};

