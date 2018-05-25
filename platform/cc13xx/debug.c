/*
 * Copyright (c) 2016 Brian Swetland
 * Copyright 2018 The DEOS Authors
 */

#include <kernel/thread.h>
#include <platform/debug.h>

#include <driverlib/uart.h>

#define UART0_BASE 0x40001000

void platform_dputc(char c) {
	UARTCharPut(UART0_BASE, c);
}

int platform_dgetc(char *c, bool wait) {
	int n;
	for (;;) {
		if ((n = UARTCharGetNonBlocking(UART0_BASE)) < 0) {
			if (wait) {
				thread_yield();
			} else {
				return -1;
			}
		} else {
			*c = n;
			return 0;
		}
	}
}
