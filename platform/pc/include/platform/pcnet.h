/*
 * Copyright (c) 2013 Corey Tabaka
 * Copyright 2018 The DEOS Authors
 */

#ifndef __PLATFORM_PCNET_H
#define __PLATFORM_PCNET_H

#include <stdint.h>

struct platform_pcnet_config {
    uint16_t vendor_id;
    uint16_t device_id;
    int index;
};

#endif



