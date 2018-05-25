/*
 * Copyright (c) 2015 Travis Geiselbrecht
 * * Copyright 2018 The DEOS Authors
 */

#if WITH_LIB_MINIP
#include <app.h>

#include <platform.h>
#include <stdio.h>
#include <debug.h>
#include <string.h>
#include <pow2.h>
#include <err.h>
#include <assert.h>
#include <trace.h>

#include <app/lkboot.h>

#include "lkboot.h"

#include <lib/minip.h>

#define LOCAL_TRACE 0

static ssize_t tcp_readx(void *s, void *_data, size_t len) {
    char *data = _data;
    while (len > 0) {
        int r = tcp_read(s, data, len);
        if (r <= 0) return -1;
        data += r;
        len -= r;
    }
    return 0;
}

lkb_t *lkboot_tcp_opened(void *s)
{
    lkb_t *lkb;

    lkb = lkboot_create_lkb(s, tcp_readx, (void *)tcp_write);
    if (!lkb)
        return NULL;

    return lkb;
}

#endif
