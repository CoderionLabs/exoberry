/*
 * Copyright (c) 2013 Corey Tabaka
 * Copyright 2018 The DEOS Authors
 */
#ifndef __DEV_CLASS_FB_H
#define __DEV_CLASS_FB_H

#include <compiler.h>
#include <dev/driver.h>

struct fb_info {
    void *addr;
    size_t line_width;
    size_t width;
    size_t height;
    size_t bpp;
};

/* fb interface */
struct fb_ops {
    struct driver_ops std;

    status_t (*set_mode)(struct device *dev, size_t width, size_t height, size_t bpp);
    status_t (*get_info)(struct device *dev, struct fb_info *info);
    status_t (*update)(struct device *dev);
    status_t (*update_region)(struct device *dev, size_t x, size_t y, size_t width, size_t height);
};

__BEGIN_CDECLS

status_t class_fb_set_mode(struct device *dev, size_t width, size_t height, size_t bpp);
status_t class_fb_get_info(struct device *dev, struct fb_info *info);
status_t class_fb_update(struct device *dev);
status_t class_fb_update_region(struct device *dev, size_t x, size_t y, size_t width, size_t height);

__END_CDECLS

#endif


