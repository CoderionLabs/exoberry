/*
 * Copyright (c) 2013 Google, Inc.
 * Copyright 2018 The DEOS Authors
 */
#ifndef __LIB_VERSION_H
#define __LIB_VERSION_H

#include <compiler.h>

__BEGIN_CDECLS

#define VERSION_STRUCT_VERSION 0x1

typedef struct {
    unsigned int struct_version;
    const char *arch;
    const char *platform;
    const char *target;
    const char *project;
    const char *buildid;
} lk_version_t;

extern const lk_version_t version;

void print_version(void);

__END_CDECLS

#endif

