/*
 * Copyright (c) 2014 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#ifndef __PLATFORM_GIC_H
#define __PLATFORM_GIC_H

#include <platform/zynq.h>

#define GICBASE(n)  (CPUPRIV_BASE)
#define GICC_OFFSET (0x0100)
#define GICD_OFFSET (0x1000)

#endif
