/*
 * Copyright (c) 2008-2014 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#include <rand.h>
#include <sys/types.h>

static unsigned int randseed = 12345;

void srand(unsigned int seed)
{
    randseed = seed;
}

void rand_add_entropy(const void *buf, size_t len)
{
    if (len == 0)
        return;

    uint32_t enp = 0;
    for (size_t i = 0; i < len; i++) {
        enp ^= ((enp << 8) | (enp >> 24)) ^ ((const uint8_t *)buf)[i];
    }

    randseed ^= enp;
}

int rand(void)
{
    return (randseed = randseed * 1664525 + 1013904223);
}
