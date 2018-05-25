/*
 * Copyright (c) 2008-2015 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <lib/io.h>

#include <err.h>
#include <ctype.h>
#include <debug.h>
#include <assert.h>

ssize_t io_write(io_handle_t *io, const char *buf, size_t len)
{
    DEBUG_ASSERT(io->magic == IO_HANDLE_MAGIC);

    if (!io->hooks->write)
        return ERR_NOT_SUPPORTED;

    return io->hooks->write(io, buf, len);
}

ssize_t io_read(io_handle_t *io, char *buf, size_t len)
{
    DEBUG_ASSERT(io->magic == IO_HANDLE_MAGIC);

    if (!io->hooks->read)
        return ERR_NOT_SUPPORTED;

    return io->hooks->read(io, buf, len);
}

