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
strncpy(char *dest, char const *src, size_t count)
{
    char *tmp = dest;

    while (count-- && (*dest++ = *src++) != '\0')
        ;

    return tmp;
}

