/*
 * Copyright (c) 2015 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <compiler.h>

__BEGIN_CDECLS;

struct miniheap_stats {
    void *heap_start;
    size_t heap_len;
    size_t heap_free;
    size_t heap_max_chunk;
    size_t heap_low_watermark;
};

void miniheap_get_stats(struct miniheap_stats *ptr);

void *miniheap_alloc(size_t, unsigned int alignment);
void *miniheap_realloc(void *, size_t);
void miniheap_free(void *);

void miniheap_init(void *ptr, size_t len);
void miniheap_dump(void);
void miniheap_trim(void);

__END_CDECLS;
