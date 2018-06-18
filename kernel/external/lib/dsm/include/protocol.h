#pragma once

#include <sys/types.h>
#include <kernel/mutex.h>
#include "lwip/opt.h"
#include "lwip/sockets.h"
#include "lwip/api.h"
#include "lwip/sys.h"
#include "lwip/igmp.h"
#include "lwip/inet.h"
#include "lwip/tcp.h"
#include "lwip/raw.h"
#include "lwip/udp.h"
#include "lwip/tcpip.h"
#include "lwip/pbuf.h"

#include <string.h>

#include <uthash.h>
#include <message.h>
#include <socket.h>


typedef int (*dsm_proto_message_handler_f)(uint32_t peer_id, dsm_message *msg)

struct dsm_proto_message_handler{
    int message_type;
    dsm_proto_message_handler_f handler_func;
    UT_hash_handle hh;
};

struct dsm_proto_peer_id{
    uint32_t id;
    struct dsm_proto_peer_id *next;
};

struct peer_information{
    uint32_t id;
    int sock_fd;
    struct sockaddr_storage addr;
    mutex_t send_lock;
    UT_hash_handle hh;
}

void dsm_proto_listener_init(unsigned short port);
void dsm_proto_shutdown();

struct dsm_proto_peer_id *dsm_proto_peer_id_create(uint32_t peer_id);
struct dsm_proto_peer_id *dsm_proto_get_peer_ids();

uint32_t dsm_proto_local_id();
int dsm_proto_send(uint32_t peer_id, uint32_t msg_type, dsm_message *msg);
int dsm_proto_register_handler(int message_type, dsm_proto_message_handler_f handler_f);
int dsm_proto_group_join(char* hostname, unsigned short port);



