/*
 * Copyright 2018 The Fuchsia Authors. All Rights Reserved.
 * Copyright 2018 The DEOS Authors
 */

#pragma once

#include <dev/usb/class/cdcserial.h>

/* This needs to be called before app_init. */
void cdctest_setup(cdcserial_channel_t *chan);
