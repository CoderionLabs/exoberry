/*
 * Copyright (c) 2009 Corey Tabaka
 * Copyright 2018 The DEOS Authors
 */
#include <arch/ops.h>

/* nothing to do to sync I & D cache on x86 */
void arch_sync_cache_range(addr_t start, size_t len)
{
}
