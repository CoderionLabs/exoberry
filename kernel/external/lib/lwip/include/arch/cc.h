/*
 * Copyright (c) 2013 Corey Tabaka
 * Copyright 2018 The DEOS Authors
 */
#ifndef __LIB_LWIP_ARCH_CC_H
#define __LIB_LWIP_ARCH_CC_H

#include <stdint.h>
#include <endian.h>
#include <stdio.h>
#include <compiler.h>

typedef uint8_t u8_t;
typedef uint16_t u16_t;
typedef uint32_t u32_t;
typedef int8_t s8_t;
typedef int16_t s16_t;
typedef int32_t s32_t;

typedef intptr_t mem_ptr_t;

#define U16_F "u"
#define S16_F "d"
#define X16_F "x"
#define U32_F "u"
#define S32_F "d"
#define X32_F "x"
#define SZT_F "zu"

#define LWIP_CHKSUM_ALGORITHM 2

#define LWIP_PLATFORM_DIAG(x) do {} while (0)
#define LWIP_PLATFORM_ASSERT(x) do {} while (0)

#define PACK_STRUCT_STRUCT __PACKED

#endif

