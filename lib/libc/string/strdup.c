/*
** Copyright 2004, Travis Geiselbrecht. All rights reserved.
** Distributed under the terms of the NewOS License.
*/
/*
 * Copyright (c) 2008 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <stdlib.h>
#include <string.h>

char *
strdup(const char *str)
{
    size_t len;
    char *copy;

    len = strlen(str) + 1;
    copy = malloc(len);
    if (copy == NULL)
        return NULL;
    memcpy(copy, str, len);
    return copy;
}

