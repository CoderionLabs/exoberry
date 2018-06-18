/*
 * Copyright (c) 2014 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#ifndef __IOVEC_H
#define __IOVEC_H

#include <compiler.h>
#include <stddef.h>
#include <sys/types.h>

__BEGIN_CDECLS;

typedef struct iovec {
    void *iov_base;
    size_t iov_len;
} iovec_t;

ssize_t iovec_size(const iovec_t *iov, uint iov_cnt);

ssize_t iovec_to_membuf(uint8_t *buf, uint buf_len,
                        const iovec_t *iov, uint iov_cnt, uint iov_pos);

__END_CDECLS;

#endif

