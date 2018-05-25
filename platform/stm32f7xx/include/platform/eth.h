/*
 * Copyright (c) 2015 Carlos Pizano-Uribe <cpu@chromium.org>
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <stdint.h>
#include <sys/types.h>

/* ethernet driver public api */
typedef enum {
    PHY_LAN8742A,     // Microchip.
    PHY_DP83848,      // Texas Instruments.
    PHY_KSZ8721,      // Micrel
} eth_phy_itf;

struct pktbuf;

status_t eth_init(const uint8_t *mac_addr, eth_phy_itf eth_phy);
status_t stm32_eth_send_minip_pkt(struct pktbuf *p);

