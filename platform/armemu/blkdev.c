/*
 * Copyright (c) 2010 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <err.h>
#include <debug.h>
#include <trace.h>
#include <platform.h>
#include "platform_p.h"
#include <platform/armemu.h>
#include <lib/bio.h>
#include <reg.h>

static bdev_t dev;

static uint64_t get_blkdev_len(void)
{
    return *REG64(BDEV_LEN);
}

ssize_t read_block(struct bdev *dev, void *buf, bnum_t block, uint count)
{
    /* assume args have been validated by layer above */
    *REG32(BDEV_CMD_ADDR) = (uint32_t)buf;
    *REG64(BDEV_CMD_OFF) = (uint64_t)((uint64_t)block * dev->block_size);
    *REG32(BDEV_CMD_LEN) = count * dev->block_size;

    *REG32(BDEV_CMD) = BDEV_CMD_READ;

    uint32_t err = *REG32(BDEV_CMD) & BDEV_CMD_ERRMASK;
    if (err == BDEV_CMD_ERR_NONE)
        return count * dev->block_size;
    else
        return ERR_IO;
}

ssize_t write_block(struct bdev *dev, const void *buf, bnum_t block, uint count)
{
    /* assume args have been validated by layer above */
    *REG32(BDEV_CMD_ADDR) = (uint32_t)buf;
    *REG64(BDEV_CMD_OFF) = (uint64_t)((uint64_t)block * dev->block_size);
    *REG32(BDEV_CMD_LEN) = count * dev->block_size;

    *REG32(BDEV_CMD) = BDEV_CMD_WRITE;

    uint32_t err = *REG32(BDEV_CMD) & BDEV_CMD_ERRMASK;
    if (err == BDEV_CMD_ERR_NONE)
        return count * dev->block_size;
    else
        return ERR_IO;
}

void platform_init_blkdev(void)
{
    if ((*REG32(SYSINFO_FEATURES) & SYSINFO_FEATURE_BLOCKDEV) == 0)
        return; // no block device

    TRACEF("device len %lld\n", get_blkdev_len());

    if (get_blkdev_len() == 0)
        return;

    bio_initialize_bdev(&dev, "block0", 512, get_blkdev_len() / 512, 0, NULL,
                        BIO_FLAGS_NONE);

    // fill in hooks
    dev.read_block = &read_block;
    dev.write_block = &write_block;

    bio_register_device(&dev);
}

