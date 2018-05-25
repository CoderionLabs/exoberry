/*
 * Copyright (c) 2015 Gurjant Kalsi <me@gurjantkalsi.com>
 * Copyright 2018 The DEOS Authors
 */

#ifndef LIB_FS_SPIFS_H_
#define LIB_FS_SPIFS_H_

#include <lib/fs.h>

#define DEAULT_SPIFS_MOUNT_POINT "/spifs"
#define DEAULT_SPIFS_NAME        "spifs"

typedef struct {
    uint32_t toc_pages;
} spifs_format_args_t;

#endif  // LIB_FS_SPIFS_H_
