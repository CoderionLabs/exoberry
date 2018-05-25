/*
 * Copyright (c) 2014 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>

/* recovering boot arguments that were passed */
bool bootargs_are_valid(void);
const char *bootargs_get_command_line(void);
status_t bootargs_get_bootimage_pointer(uint64_t *offset, size_t *len, const char **device);

/* constructing boot arguments */
status_t bootargs_start(void *buf, size_t buf_len);
status_t bootargs_add_command_line(void *buf, size_t buf_len, const char *str);
status_t bootargs_add_bootimage_pointer(void *buf, size_t buf_len, const char *device, uint64_t offset, size_t len);

/* build 4 ulong arguments to pass to a second stage */
void bootargs_generate_lk_arg_values(ulong buf, ulong args[4]);

