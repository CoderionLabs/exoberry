/*
 * Copyright (c) 2013 Heather Lee Wilson
 * Copyright 2018 The DEOS Authors
 */
#ifndef __NORFS_TEST_HELPER_H
#define __NORFS_TEST_HELPER_H

#include <stddef.h>
#include <sys/types.h>
#include <lib/norfs_inode.h>

/* Tools to help test. */

uint32_t write_pointer;
uint32_t norfs_nvram_offset;

status_t find_free_block(uint32_t *ptr);
uint8_t block_num(uint32_t flash_pointer);
void dump_bank(void);
void wipe_fs(void);
status_t collect_block(uint32_t garbage_block, uint32_t *garbage_write_ptr);
bool get_inode(uint32_t key, struct norfs_inode **inode);

#endif
