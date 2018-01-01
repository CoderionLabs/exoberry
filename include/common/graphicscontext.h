/*
 * Created on Mon Jan 01 2018
 *
 * Copyright (c) 2018 Friedrich Doku
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 or later as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details
 *
 */

#ifndef __DEOS__COMMON__GRAPHICSCONTEXT_H
#define __DEOS__COMMON__GRAPHICSCONTEXT_H

#include <drivers/vga.h>

namespace DEOS
{
    namespace common
    {
        typedef DEOS::drivers::VideoGraphicsArray GraphicsContext;
    }
}

#endif
