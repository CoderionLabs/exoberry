/*
 * Copyright (c) 2014 Chris Anderson
 * Copyright 2018 The DEOS Authors
 */

#include "minip-internal.h"

/* XXX alternate implementation, merge */
uint16_t ones_sum16(uint32_t sum, const void *_buf, int len)
{
    const uint16_t *buf = _buf;

    while (len >= 2) {
        sum += *buf++;
        if (sum & 0x80000000)
            sum = (sum & 0xffff) + (sum >> 16);
        len -= 2;
    }

    if (len) {
        uint16_t temp = htons((*(uint8_t *)buf) << 8);
        sum += temp;
    }

    while (sum >> 16)
        sum = (sum & 0xffff) + (sum >> 16);

    return sum;
}

uint16_t rfc1701_chksum(const uint8_t *buf, size_t len)
{
    uint32_t total = 0;
    uint16_t chksum = 0;
    const uint16_t *p = (const uint16_t *) buf;

    // Length is in bytes
    for (size_t i = 0; i < len / 2; i++ ) {
        total += p[i];
    }

    chksum = (total & 0xFFFF) + (total >> 16);
    chksum = ~chksum;

    return chksum;
}

#if MINIP_USE_UDP_CHECKSUM
uint16_t rfc768_chksum(struct ipv4_hdr *ipv4, struct udp_hdr *udp)
{
    uint32_t total = 0;
    uint16_t chksum = 0;
    size_t len = ntohs(udp->len);
    uint16_t *p;

    p = (uint16_t *)ipv4->src_addr;
    total += htons(p[0]);
    total += htons(p[1]);

    p = (uint16_t *)ipv4->dst_addr;
    total += htons(p[0]);
    total += htons(p[1]);

    p = (const uint16_t *)udp->data;
    for (size_t i = 0; i < len / 2; i++ ) {
        total += p[i];
    }

    total += IP_PROTO_UDP;
    total += udp->len;
    total += udp->src_port;
    total += udp->dst_port;
    total += ipv4->len;

    chksum = (total & 0xFFFF) + (total >> 16);
    chksum = ~chksum;

    return chksum;
}
#endif
