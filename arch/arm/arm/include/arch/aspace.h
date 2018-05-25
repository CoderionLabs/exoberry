/*
 * Copyright (c) 2015-2016 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <compiler.h>
#include <list.h>

__BEGIN_CDECLS

struct arch_aspace {
    /* pointer to the translation table */
    paddr_t tt_phys;
    uint32_t *tt_virt;

    /* range of address space */
    vaddr_t base;
    size_t size;

    /* list of pages allocated for these page tables */
    struct list_node pt_page_list;
};

__END_CDECLS
