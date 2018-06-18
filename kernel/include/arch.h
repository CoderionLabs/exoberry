/*
 * Copyright (c) 2008-2014 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#ifndef __ARCH_H
#define __ARCH_H

#include <compiler.h>
#include <sys/types.h>

__BEGIN_CDECLS

void arch_early_init(void);
void arch_init(void);
void arch_quiesce(void);
void arch_chain_load(void *entry, ulong arg0, ulong arg1, ulong arg2, ulong arg3) __NO_RETURN;
void arch_enter_uspace(vaddr_t entry_point, vaddr_t user_stack_top) __NO_RETURN;

__END_CDECLS

/* arch specific bits */
#include <arch/defines.h>

#endif
