/*
 * Copyright (c) 2013 Google, Inc.
 * Copyright 2018 The DEOS Authors
 */
#ifndef __LIB_BUILDSIG_H
#define __LIB_BUILDSIG_H

#include <stddef.h>
#include <sys/types.h>
#include <lib/version.h>

/* routines for searching for and finding a build signature */
status_t buildsig_search(const void *ptr, size_t search_len, size_t max_len,
                         const lk_version_t **version);

#define DEFAULT_BUILDSIG_SEARCH_LEN 1024

#endif

