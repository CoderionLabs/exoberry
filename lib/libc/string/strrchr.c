/*
** Copyright 2001, Manuel J. Petit. All rights reserved.
** Distributed under the terms of the NewOS License.
*/
/*
 * Copyright (c) 2008 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <string.h>
#include <sys/types.h>

char *
strrchr(char const *s, int c)
{
    char const *last= c?0:s;


    while (*s) {
        if (*s== c) {
            last= s;
        }

        s+= 1;
    }

    return (char *)last;
}
