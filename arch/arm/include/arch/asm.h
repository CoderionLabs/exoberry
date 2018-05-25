/*
 * Copyright (c) 2014 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <arch/arm/cores.h>

#if ARM_ARCH_LEVEL >= 7
#define LOADCONST(reg, c) \
    movw reg, #:lower16: c; \
    movt reg, #:upper16: c
#else
#define LOADCONST(reg, c) ldr   reg, =##c
#endif

