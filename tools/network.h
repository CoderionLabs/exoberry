/*
 * Copyright (c) 2014 Brian Swetland
 * Copyright 2018 The DEOS Authors
 */
#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int udp_listen(in_addr_t addr, unsigned port, int shared);
int udp_connect(in_addr_t addr, unsigned port);

int tcp_listen(in_addr_t addr, unsigned port);
int tcp_connect(in_addr_t addr, unsigned port);

in_addr_t lookup_hostname(const char *hostname);
