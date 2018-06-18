/*
 * Copyright (c) 2015 Steve White
 * Copyright 2018 The DEOS Authors
 */

#ifndef __FAT32_H
#define __FAT32_H

#include <lib/bio.h>
#include <lib/fs.h>

typedef void *fsfilecookie;

status_t fat32_mount(bdev_t *dev, fscookie **cookie);
status_t fat32_unmount(fscookie *cookie);

/* file api */
status_t fat32_open_file(fscookie *cookie, const char *path, filecookie **fcookie);
ssize_t fat32_read_file(filecookie *fcookie, void *buf, off_t offset, size_t len);
status_t fat32_close_file(filecookie *fcookie);
status_t fat32_stat_file(filecookie *fcookie, struct file_stat *stat);

#endif

