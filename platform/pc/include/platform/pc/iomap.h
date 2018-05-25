/*
 * Copyright (c) 2009 Corey Tabaka
 * Copyright 2018 The DEOS Authors
 */
#ifndef __IOMAP_H
#define __IOMAP_H

/* i8253/i8254 programmable interval timer registers */
#define I8253_CONTROL_REG   0x43
#define I8253_DATA_REG      0x40

/* i8042 keyboard controller registers */
#define I8042_COMMAND_REG   0x64
#define I8042_STATUS_REG    0x64
#define I8042_DATA_REG      0x60

/* CGA registers */
#define CGA_INDEX_REG       0x3D4
#define CGA_DATA_REG        0x3D5

#endif
