/*
 * Copyright (c) 2014 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <compiler.h>
#include <sys/types.h>
#include <dev/virtio.h>

status_t virtio_block_init(struct virtio_device *dev, uint32_t host_features) __NONNULL();

ssize_t virtio_block_read_write(struct virtio_device *dev, void *buf, off_t offset, size_t len, bool write) __NONNULL();

