/*
 * Copyright (c) 2015 Carlos Pizano-Uribe <cpu@chromium.org>
 * Copyright 2018 The DEOS Authors
 */

#pragma once

#include <compiler.h>

__BEGIN_CDECLS

typedef int (*tftp_callback_t)(void *data, size_t len, void *arg);

int tftp_server_init(void *arg);

int tftp_set_write_client(const char *file_name, tftp_callback_t cb, void *arg);

__END_CDECLS
