/*
 * Copyright (c) 2010 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#ifndef __LIB_FONT_H
#define __LIB_FONT_H

#include <lib/gfx.h>
#include <compiler.h>

#define FONT_X  6
#define FONT_Y  12

__BEGIN_CDECLS

void font_draw_char(gfx_surface *surface, unsigned char c, int x, int y, uint32_t color);

__END_CDECLS

#endif

