/*
 * Copyright (c) 2013 Corey Tabaka
 * Copyright 2018 The DEOS Authors
 */
#ifndef __DEV_CLASS_NETIF_H
#define __DEV_CLASS_NETIF_H

#include <list.h>
#include <compiler.h>
#include <dev/driver.h>

struct netstack_state;
struct pbuf;

/* netif interface */
struct netif_ops {
    struct driver_ops std;

    status_t (*set_state)(struct device *dev, struct netstack_state *state);
    ssize_t (*get_hwaddr)(struct device *dev, void *buf, size_t max_len);
    ssize_t (*get_mtu)(struct device *dev);

    status_t (*set_status)(struct device *dev, bool up);
    status_t (*output)(struct device *dev, struct pbuf *p);
    status_t (*mcast_filter)(struct device *dev, const uint8_t *mac, int action);
};

__BEGIN_CDECLS

/* netif API */
status_t class_netif_set_state(struct device *dev, struct netstack_state *state);
ssize_t class_netif_get_hwaddr(struct device *dev, void *buf, size_t max_len);
ssize_t class_netif_get_mtu(struct device *dev);
status_t class_netif_set_status(struct device *dev, bool up);
status_t class_netif_output(struct device *dev, struct pbuf *p);
status_t class_netif_mcast_filter(struct device *dev, const uint8_t *mac, int action);

status_t class_netif_add(struct device *dev);

/* network stack API - called by drivers */
status_t class_netstack_input(struct device *dev, struct netstack_state *state, struct pbuf *p);

status_t class_netstack_wait_for_network(lk_time_t timeout);

__END_CDECLS

#endif

