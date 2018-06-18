/*
 * Copyright (c) 2008 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#ifndef __NEW_H
#define __NEW_H

#include <sys/types.h>

void *operator new(size_t);
void *operator new(size_t, void *ptr);
void *operator new[](size_t);
void *operator new[](size_t, void *ptr);
void operator delete(void *p);
void operator delete[](void *p);

#endif
