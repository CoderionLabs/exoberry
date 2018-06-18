/*
 * Copyright (c) 2016 Brian Swetland
 * Copyright 2018 The DEOS Authors
 */

#pragma once

#include <platform/ti-rf.h>
#include <platform/ti-rf-prop.h>

void radio_init(void);

uint32_t radio_send_cmd(uint32_t cmd);
void radio_wait_cmd(uint16_t *status);



