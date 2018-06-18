/*
 * Copyright (c) 2015 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#pragma once

/* zybo-microblaze is a project running on zybo */
#define MDM_BASEADDR        0x40000000
#define TIMER_BASEADDR      0x40001000
#define GPIO_BASEADDR       0x40002000
#define INTC_BASEADDR       0x40003000
#define UARTLITE_BASEADDR   0x40004000

#define TIMER_IRQ           0
#define GPIO_IRQ            1
#define MDM_IRQ             2
#define UARTLITE_IRQ        3
#define MAX_INT             4

#define TIMER_RATE (100000000)

