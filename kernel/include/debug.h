/*
 * Copyright (c) 2008-2012 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <stddef.h>
#include <stdio.h>
#include <compiler.h>
#include <platform/debug.h>

#if !defined(LK_DEBUGLEVEL)
#define LK_DEBUGLEVEL 0
#endif

/* debug levels */
#define CRITICAL 0
#define ALWAYS 0
#define INFO 1
#define SPEW 2

__BEGIN_CDECLS

#if !DISABLE_DEBUG_OUTPUT

/* Obtain the panic file descriptor. */
FILE *get_panic_fd(void);

/* dump memory */
void hexdump(const void *ptr, size_t len);
void hexdump8_ex(const void *ptr, size_t len, uint64_t disp_addr_start);

#else

/* Obtain the panic file descriptor. */
static inline FILE *get_panic_fd(void) { return NULL; }

/* dump memory */
static inline void hexdump(const void *ptr, size_t len) { }
static inline void hexdump8_ex(const void *ptr, size_t len, uint64_t disp_addr_start) { }

#endif /* DISABLE_DEBUG_OUTPUT */

static inline void hexdump8(const void *ptr, size_t len)
{
    hexdump8_ex(ptr, len, (uint64_t)((addr_t)ptr));
}

#define dprintf(level, x...) do { if ((level) <= LK_DEBUGLEVEL) { printf(x); } } while (0)

/* systemwide halts */
void _panic(void *caller, const char *fmt, ...) __PRINTFLIKE(2, 3) __NO_RETURN;
#define panic(x...) _panic(__GET_CALLER(), x)

#define PANIC_UNIMPLEMENTED panic("%s unimplemented\n", __PRETTY_FUNCTION__)

/* spin the cpu for a period of (short) time */
void spin(uint32_t usecs);

/* spin the cpu for a certain number of cpu cycles */
void spin_cycles(uint32_t usecs);

__END_CDECLS
