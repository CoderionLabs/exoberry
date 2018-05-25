/*
 * Copyright (c) 2008 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#ifndef __PLATFORM_DEBUG_H
#define __PLATFORM_DEBUG_H

#include <sys/types.h>
#include <stdbool.h>
#include <stdarg.h>
#include <compiler.h>

__BEGIN_CDECLS

void platform_dputc(char c);
int platform_dgetc(char *c, bool wait);

// Should be available even if the system has panicked.
void platform_pputc(char c);
int platform_pgetc(char *c, bool wait);

__END_CDECLS

#endif

