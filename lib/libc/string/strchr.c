/*
** Copyright 2001, Travis Geiselbrecht. All rights reserved.
** Distributed under the terms of the NewOS License.
*/
/*
 * Copyright (c) 2008 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <string.h>
#include <sys/types.h>

char *
strchr(const char *s, int c)
{
    for (; *s != (char) c; ++s)
        if (*s == '\0')
            return NULL;
    return (char *) s;
}
