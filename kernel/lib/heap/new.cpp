/*
 * Copyright (c) 2006-2015 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <new.h>
#include <debug.h>
#include <lib/heap.h>

void *operator new(size_t s)
{
    return malloc(s);
}

void *operator new[](size_t s)
{
    return malloc(s);
}

void *operator new(size_t , void *p)
{
    return p;
}

void operator delete(void *p)
{
    return free(p);
}

void operator delete[](void *p)
{
    return free(p);
}

