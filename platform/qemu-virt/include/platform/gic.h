/*
 * Copyright (c) 2014-2015 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <platform/qemu-virt.h>

#define GICBASE(n)  (CPUPRIV_BASE_VIRT)
#define GICD_OFFSET (0x00000)
#define GICC_OFFSET (0x10000)

