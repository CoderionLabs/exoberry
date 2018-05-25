/*
 * Copyright (c) 2015 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <compiler.h>

__BEGIN_CDECLS;

void *cmpct_alloc(size_t);
void *cmpct_realloc(void *, size_t);
void cmpct_free(void *);
void *cmpct_memalign(size_t size, size_t alignment);

void cmpct_init(void);
void cmpct_dump(void);
void cmpct_test(void);
void cmpct_trim(void);

__END_CDECLS;
