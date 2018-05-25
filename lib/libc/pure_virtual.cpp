/*
 * Copyright (c) 2006 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <debug.h>

extern "C" void __cxa_pure_virtual(void)
{
    panic("pure virtual called\n");
}

extern "C" int __cxa_atexit(void (*destructor)(void *), void *arg, void *__dso_handle)
{
    return 0;
}

