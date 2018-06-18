/*
 * Copyright (c) 2009 Corey Tabaka
 * Copyright (c) 2015 Intel Corporation
 * Copyright 2018 The DEOS Authors
 */
#ifndef __PLATFORM_PC_H
#define __PLATFORM_PC_H

#include <platform/pc/memmap.h>
#include <platform/pc/iomap.h>

/* NOTE: keep arch/x86/crt0.S in sync with these definitions */

/* interrupts */
#define INT_VECTORS 0x31

/* defined interrupts */
#define INT_BASE            0x20
#define INT_PIT             0x20
#define INT_KEYBOARD        0x21
#define INT_PIC2            0x22

#define INT_BASE2           0x28
#define INT_CMOSRTC         0x28
#define INT_PS2MOUSE        0x2c
#define INT_IDE0            0x2e
#define INT_IDE1            0x2f

/* APIC vectors */
#define INT_APIC_TIMER      0x22

/* PIC remap bases */
#define PIC1_BASE 0x20
#define PIC2_BASE 0x28

#endif

