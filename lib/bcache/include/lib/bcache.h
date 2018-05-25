/*
 * Copyright (c) 2007 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <lib/bio.h>

typedef void *bcache_t;

bcache_t bcache_create(bdev_t *dev, size_t block_size, int block_count);
void bcache_destroy(bcache_t);

int bcache_read_block(bcache_t, void *, uint block);

// get and put a pointer directly to the block
int bcache_get_block(bcache_t, void **, uint block);
int bcache_put_block(bcache_t, uint block);

