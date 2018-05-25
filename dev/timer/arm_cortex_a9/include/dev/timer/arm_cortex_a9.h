/*
 * Copyright (c) 2014 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <sys/types.h>

void arm_cortex_a9_timer_init(addr_t scu_control_base, uint32_t freq);
