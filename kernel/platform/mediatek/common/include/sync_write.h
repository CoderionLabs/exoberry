/*
 * Copyright (c) 2015 MediaTek Inc.
 * Copyright 2018 The DEOS Authors
 */
#ifndef __SYNC_WRITE_H__
#define __SYNC_WRITE_H__

#include <arch/arm.h>

#define dsb()   DSB

#define mt_reg_sync_writel(v, a) \
        do {    \
            *(volatile unsigned int *)(a) = (v);    \
            dsb(); \
        } while (0)

#define mt_reg_sync_writew(v, a) \
        do {    \
            *(volatile unsigned short *)(a) = (v);    \
            dsb(); \
        } while (0)

#define mt_reg_sync_writeb(v, a) \
        do {    \
            *(volatile unsigned char *)(a) = (v);    \
            dsb(); \
        } while (0)

#endif /* !__SYNC_WRITE_H__ */

