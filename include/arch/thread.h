/*
 * Copyright (c) 2008 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#ifndef __ARCH_THREAD_H
#define __ARCH_THREAD_H

// give the arch code a chance to declare the arch_thread struct
#include <arch/arch_thread.h>

struct thread;

void arch_thread_initialize(struct thread *);
void arch_context_switch(struct thread *oldthread, struct thread *newthread);

#endif
