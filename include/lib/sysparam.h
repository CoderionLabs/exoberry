/*
 * Copyright (c) 2013, Google, Inc. All rights reserved
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <stdbool.h>
#include <sys/types.h>
#include <lib/bio.h>

#ifndef SYSPARAM_ALLOW_WRITE
#define SYSPARAM_ALLOW_WRITE 0
#endif

status_t sysparam_scan(bdev_t *bdev, off_t offset, size_t len);
status_t sysparam_reload(void);

void sysparam_dump(bool show_all);

ssize_t sysparam_length(const char *name);
ssize_t sysparam_read(const char *name, void *data, size_t len);
status_t sysparam_get_ptr(const char *name, const void **ptr, size_t *len);

#if SYSPARAM_ALLOW_WRITE
status_t sysparam_add(const char *name, const void *value, size_t len);
status_t sysparam_remove(const char *name);
status_t sysparam_lock(const char *name);
status_t sysparam_write(void);
#endif

