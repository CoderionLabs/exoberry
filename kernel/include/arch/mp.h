/*
 * Copyright (c) 2014 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <sys/types.h>
#include <kernel/mp.h>

/* send inter processor interrupt, if supported */
status_t arch_mp_send_ipi(mp_cpu_mask_t target, mp_ipi_t ipi);

void arch_mp_init_percpu(void);
