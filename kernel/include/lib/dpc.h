/*
 * Copyright (c) 2008 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#ifndef __KERNEL_DPC_H
#define __KERNEL_DPC_H

#include <list.h>
#include <sys/types.h>

typedef void (*dpc_callback)(void *arg);

#define DPC_FLAG_NORESCHED 0x1

status_t dpc_queue(dpc_callback, void *arg, uint flags);

#endif

