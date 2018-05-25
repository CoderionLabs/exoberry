/*
 * Copyright (c) 2014 Brian Swetland
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <sys/types.h>
#include <stdbool.h>

status_t zynq_program_fpga(paddr_t physaddr, size_t length);
bool zync_fpga_config_done(void);
void zynq_reset_fpga(void);

