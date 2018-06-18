/*
 * Copyright (c) 2008 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#ifndef __ASSERT_H
#define __ASSERT_H

#include <compiler.h>
#include <debug.h>

#define ASSERT(x) \
    do { if (unlikely(!(x))) { panic("ASSERT FAILED at (%s:%d): %s\n", __FILE__, __LINE__, #x); } } while (0)

#if LK_DEBUGLEVEL > 1
#define DEBUG_ASSERT(x) \
    do { if (unlikely(!(x))) { panic("DEBUG ASSERT FAILED at (%s:%d): %s\n", __FILE__, __LINE__, #x); } } while (0)
#else
#define DEBUG_ASSERT(x) \
    do { } while(0)
#endif

#define assert(e) DEBUG_ASSERT(e)

#ifndef __cplusplus
#define static_assert(e) STATIC_ASSERT(e)
#endif

#endif
