/*
 * Copyright (c) 2015-2016 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <compiler.h>
#include <list.h>
#include <arch/arm64/mmu.h>

__BEGIN_CDECLS

struct arch_aspace {
    /* pointer to the translation table */
    paddr_t tt_phys;
    pte_t *tt_virt;

    uint flags;

    /* range of address space */
    vaddr_t base;
    size_t size;
};

__END_CDECLS

