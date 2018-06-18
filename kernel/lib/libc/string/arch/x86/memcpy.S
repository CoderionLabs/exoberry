/*
 * Copyright (c) 2009 Corey Tabaka
 * Copyright 2018 The DEOS Authors
 */
#include <asm.h>

/* TODO: */

.text
.align 2

/* void bcopy(const void *src, void *dest, size_t n); */
FUNCTION(bcopy)
    ret

/* void *memcpy(void *dest, const void *src, size_t n); */
FUNCTION(memmove)
FUNCTION(memcpy)
    ret

