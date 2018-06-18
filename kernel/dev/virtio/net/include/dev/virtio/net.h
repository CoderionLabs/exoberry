/*
 * Copyright (c) 2015 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <compiler.h>
#include <sys/types.h>
#include <dev/virtio.h>

status_t virtio_net_init(struct virtio_device *dev, uint32_t host_features) __NONNULL();
status_t virtio_net_start(void);

/* return the count of virtio interfaces found */
int virtio_net_found(void);

status_t virtio_net_get_mac_addr(uint8_t mac_addr[6]);

struct pktbuf;
extern status_t virtio_net_send_minip_pkt(struct pktbuf *p);

