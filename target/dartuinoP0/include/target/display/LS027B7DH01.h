/*
 * Copyright (c) 2015 Gurjant Kalsi <me@gurjantkalsi.com>
 * Copyright 2018 The DEOS Authors
 */

// 2.7 Inch Monocromatic Sharp Memory LCD

#pragma once

#include <dev/display.h>

#define MLCD_WIDTH  ((uint16_t)400)
#define MLCD_HEIGHT ((uint16_t)240)

// Ensure width corresponds to an integral number of bytes
STATIC_ASSERT((MLCD_WIDTH & 0x3) == 0);

// 1 bit per pixel divided by 8 bits per byte
#define MLCD_BYTES_LINE  (MLCD_WIDTH / 8)
#define MLCD_FORMAT      (DISPLAY_FORMAT_MONO_1)

uint8_t lcd_get_line(struct display_image *image, uint8_t idx, uint8_t *result);
