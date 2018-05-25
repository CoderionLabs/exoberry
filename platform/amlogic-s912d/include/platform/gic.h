/*
 * Copyright (c) 2018 The Fuchsia Authors
 * Copyright 2018 The DEOS Authors
 */

#pragma once

#include <platform/s912d.h>

#define GICBASE(n) (GIC_BASE)
#define GICD_OFFSET (0x1000)
#define GICC_OFFSET (0x2000)

#define MAX_INT 255