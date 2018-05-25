/*
 * Copyright (c) 2013 Google, Inc.
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <sys/types.h>
#include <iovec.h>
#include <compiler.h>
#include <stdarg.h>

#if WITH_LIB_KLOG

#define KLOG_CURRENT_BUFFER -1

void klog_init(void);

ssize_t klog_recover(void *ptr);
status_t klog_create(void *ptr, size_t len, uint count);

uint klog_buffer_count(void);
uint klog_current_buffer(void);
status_t klog_set_current_buffer(uint buffer);

/* dump the klog to the console, -1 is current buffer */
void klog_dump(int buffer);

/*
 * Fill in an iovec that points to the requested buffer, -1 is current buffer.
 * The buffer may be in 2 pieces, due to the internal circular buffer.
 * Return is number of iovec runs.
 */
int klog_get_buffer(int buffer, iovec_t *vec);

/*
 * Read functions actively remove data from the klog on read
 */
ssize_t klog_read(char *buf, size_t len, int buf_id);
char klog_getc(int buf_id);
char klog_getchar(void);
bool klog_has_data(void);

void klog_putchar(char c);
void klog_puts(const char *str);
void klog_printf(const char *fmt, ...) __PRINTFLIKE(1, 2);
void klog_vprintf(const char *fmt, va_list ap);

#else

/* if klog is not present, stub out the input routines */
static inline void klog_putc(char c) {}
static inline void klog_puts(const char *str) {}
static inline void klog_printf(const char *fmt, ...) {}
static inline void klog_vprintf(const char *fmt, va_list ap) {}

#endif
