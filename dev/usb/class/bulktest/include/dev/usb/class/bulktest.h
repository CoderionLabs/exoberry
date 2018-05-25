/*
 * Copyright (c) 2015 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <sys/types.h>
#include <dev/usbc.h>
#include <dev/usb.h>

status_t usb_class_bulktest_init(uint interface_num, ep_t epin, ep_t epout);

