/*
** Copyright 2002, Manuel J. Petit. All rights reserved.
** Distributed under the terms of the NewOS License.
*/
/*
 * Copyright (c) 2008 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */

#include <string.h>
#include <sys/types.h>

size_t
strlcat(char *dst, char const *src, size_t s)
{
    size_t i;
    size_t j= strnlen(dst, s);

    if (!s) {
        return j+strlen(src);
    }

    dst+= j;

    for (i= 0; ((i< s-1) && src[i]); i++) {
        dst[i]= src[i];
    }

    dst[i]= 0;

    return j + i + strlen(src+i);
}
