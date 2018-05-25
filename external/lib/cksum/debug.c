/*
 * Copyright (c) 2012 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#if WITH_LIB_CONSOLE

#include <ctype.h>
#include <debug.h>
#include <stdlib.h>
#include <stdio.h>
#include <kernel/thread.h>
#include <platform.h>
#include <lib/cksum.h>

#include <lib/console.h>

static int cmd_crc16(int argc, const cmd_args *argv);
static int cmd_crc32(int argc, const cmd_args *argv);
static int cmd_adler32(int argc, const cmd_args *argv);
static int cmd_cksum_bench(int argc, const cmd_args *argv);

STATIC_COMMAND_START
#if LK_DEBUGLEVEL > 0
STATIC_COMMAND("crc16", "crc16", &cmd_crc16)
STATIC_COMMAND("crc32", "crc32", &cmd_crc32)
STATIC_COMMAND("adler32", "adler32", &cmd_adler32)
#endif
#if LK_DEBUGLEVEL > 1
STATIC_COMMAND("bench_cksum", "benchmark the checksum routines", &cmd_cksum_bench)
#endif
STATIC_COMMAND_END(crc);

static int cmd_crc16(int argc, const cmd_args *argv)
{
    if (argc < 3) {
        printf("not enough arguments\n");
        printf("usage: %s <address> <size>\n", argv[0].str);
        return -1;
    }

    uint16_t crc = crc16(argv[1].p, argv[2].u);

    printf("0x%hx\n", crc);

    return 0;
}

static int cmd_crc32(int argc, const cmd_args *argv)
{
    if (argc < 3) {
        printf("not enough arguments\n");
        printf("usage: %s <address> <size>\n", argv[0].str);
        return -1;
    }

    uint32_t crc = crc32(0, argv[1].p, argv[2].u);

    printf("0x%x\n", crc);

    return 0;
}

static int cmd_adler32(int argc, const cmd_args *argv)
{
    if (argc < 3) {
        printf("not enough arguments\n");
        printf("usage: %s <address> <size>\n", argv[0].str);
        return -1;
    }

    uint32_t crc = adler32(0, argv[1].p, argv[2].u);

    printf("0x%x\n", crc);

    return 0;
}

static int cmd_cksum_bench(int argc, const cmd_args *argv)
{
#define BUFSIZE 0x1000
#define ITER 16384
    void *buf;
    bool freebuf;

    if (argc > 1) {
        buf = argv[1].p;
        freebuf = false;
    } else {
        buf = malloc(BUFSIZE);
        freebuf = true;
    }

    if (!buf)
        return -1;

    lk_bigtime_t t;
    uint32_t crc;

    printf("buffer at %p, size %u\n", buf, BUFSIZE);

    t = current_time_hires();
    crc = 0;
    for (int i = 0; i < ITER; i++) {
        crc = crc32(crc, buf, BUFSIZE);
    }
    t = current_time_hires() - t;

    printf("took %llu usecs to crc32 %d bytes (%lld bytes/sec)\n", t, BUFSIZE * ITER, (BUFSIZE * ITER) * 1000000ULL / t);
    thread_sleep(500);

    t = current_time_hires();
    crc = 0;
    for (int i = 0; i < ITER; i++) {
        crc = adler32(crc, buf, BUFSIZE);
    }
    t = current_time_hires() - t;

    printf("took %llu usecs to adler32 %d bytes (%lld bytes/sec)\n", t, BUFSIZE * ITER, (BUFSIZE * ITER) * 1000000ULL / t);

    if (freebuf)
        free(buf);
    return 0;
}

#endif // WITH_LIB_CONSOLE
