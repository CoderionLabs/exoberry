/*
 * Copyright (c) 2013, Google Inc. All rights reserved.
 * Copyright 2018 The DEOS Authors
 */
#ifndef __DEV_TIMER_ARM_GENERIC_H
#define __DEV_TIMER_ARM_GENERIC_H

#include <sys/types.h>

/* if freq_override != 0, use that as the operating frequency instead of CNTFRQ register */
void arm_generic_timer_init(int irq, uint32_t freq_override);

#endif

