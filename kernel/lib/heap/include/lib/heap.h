/*
 * Copyright (c) 2008-2015 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <stddef.h>
#include <sys/types.h>
#include <compiler.h>

__BEGIN_CDECLS;

/* standard heap definitions */
void *malloc(size_t size) __MALLOC;
void *memalign(size_t boundary, size_t size) __MALLOC;
void *calloc(size_t count, size_t size) __MALLOC;
void *realloc(void *ptr, size_t size) __MALLOC;
void free(void *ptr);

void heap_init(void);

/* critical section time delayed free */
void heap_delayed_free(void *);

/* tell the heap to return any free pages it can find */
void heap_trim(void);

__END_CDECLS;
