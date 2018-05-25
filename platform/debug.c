/*
 * Copyright (c) 2008-2015 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */

#include <compiler.h>
#include <debug.h>
#include <trace.h>

/* Default implementation of panic time getc/putc.
 * Just calls through to the underlying dputc/dgetc implementation
 * unless the platform overrides it.
 */
__WEAK void platform_pputc(char c)
{
    return platform_dputc(c);
}

__WEAK int platform_pgetc(char *c, bool wait)
{
    return platform_dgetc(c, wait);
}
