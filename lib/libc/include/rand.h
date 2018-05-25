/*
 * Copyright (c) 2008-2014 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#ifndef __RAND_H
#define __RAND_H

#include <compiler.h>
#include <sys/types.h>

__BEGIN_CDECLS;

int rand(void);
void srand(unsigned int seed);

/* non standard extension to add some entropy to the seed */
void rand_add_entropy(const void *buf, size_t len);

__END_CDECLS;

#endif

