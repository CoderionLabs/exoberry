/*
 * Copyright (c) 2009 Corey Tabaka
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <lib/cbuf.h>

void platform_init_keyboard(cbuf_t *buffer);

int platform_read_key(char *c);
