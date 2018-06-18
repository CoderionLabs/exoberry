/*
 * Copyright (c) 2008 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#ifndef __PLATFORM_TIMER_H
#define __PLATFORM_TIMER_H

#include <sys/types.h>

typedef enum handler_return (*platform_timer_callback)(void *arg, lk_time_t now);

status_t platform_set_periodic_timer(platform_timer_callback callback, void *arg, lk_time_t interval);

#if PLATFORM_HAS_DYNAMIC_TIMER
status_t platform_set_oneshot_timer (platform_timer_callback callback, void *arg, lk_time_t interval);
void     platform_stop_timer(void);
#endif

#endif

