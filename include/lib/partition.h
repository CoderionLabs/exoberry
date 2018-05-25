/*
 * Copyright (c) 2009 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#ifndef __LIB_PARTITION_H
#define __LIB_PARTITION_H

#include <sys/types.h>

/* examine and try to publish partitions on a particular device at a particular offset */
int partition_publish(const char *device, off_t offset);

/* remove any published subdevices on this device */
int partition_unpublish(const char *device);

#endif

