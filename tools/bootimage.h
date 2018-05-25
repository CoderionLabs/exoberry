/*
 * Copyright (c) 2014 Brian Swetland
 * Copyright 2018 The DEOS Authors
 */

#pragma once

#include <lib/bootimage_struct.h>

typedef struct bootimage bootimage;

bootimage *bootimage_init(void);

bootentry_data *bootimage_add_string(
    bootimage *img, unsigned kind, const char *s);

bootentry_file *bootimage_add_filedata(
    bootimage *img, unsigned type, void *data, unsigned len);

bootentry_file *bootimage_add_file(
    bootimage *img, unsigned type, const char *fn);

void bootimage_done(bootimage *img);

int bootimage_write(bootimage *img, int fd);
