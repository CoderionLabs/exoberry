/*
 * Copyright (c) 2015 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */

#include <errno.h>

/* completely un-threadsafe implementation of errno */
/* TODO: pull from kernel TLS or some other thread local storage */
static int _errno;

int *__geterrno(void)
{
    return &_errno;
}

