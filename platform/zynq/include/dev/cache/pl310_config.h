/*
 * Copyright (c) 2014 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <platform/zynq.h>

/* configuration for the PL310 L2 cache controller */
#define PL310_BASE L2CACHE_BASE
#define PL310_TAG_RAM_LATENCY ((1 << 8) | (1 << 4) | (1 << 0))
#define PL310_DATA_RAM_LATENCY ((1 << 8) | (2 << 4) | (1 << 0))

