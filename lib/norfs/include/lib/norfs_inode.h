/*
 * Copyright (c) 2013 Heather Lee Wilson
 * Copyright 2018 The DEOS Authors
 */
#ifndef __NORFS_INODE_H
#define __NORFS_INODE_H

#include <list.h>
#include <stdint.h>

struct norfs_inode {
    struct list_node lnode;
    uint32_t location;
    uint32_t reference_count;
};

#endif
