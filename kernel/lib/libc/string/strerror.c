/*
 * Copyright (c) 2008 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */

#include <string.h>
#include <sys/types.h>

char const *
strerror(int errnum)
{
    if (errnum < 0) {
        return "General Error";
    } else {
        return "No Error";
    }
}

