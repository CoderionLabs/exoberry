/*
 * Copyright (c) 2008 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#ifndef __DEV_ETHERNET_H
#define __DEV_ETHERNET_H

#include <sys/types.h>

/* Queue an ethernet frame for send.
**
** CRC and minimum length padding are handled by the driver.
**
** Data is malloc()'d and ownership is transferred to the ethernet
** device which will free() it once the packet is transmitted.
**
*/
int ethernet_send(void *data, unsigned length);

status_t ethernet_init(void); /* initialize the ethernet device */

#endif
