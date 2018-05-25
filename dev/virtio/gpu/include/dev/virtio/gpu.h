/*
 * Copyright (c) 2015 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <compiler.h>
#include <sys/types.h>
#include <dev/virtio.h>

status_t virtio_gpu_init(struct virtio_device *dev, uint32_t host_features) __NONNULL();

status_t virtio_gpu_start(struct virtio_device *dev) __NONNULL();

