/*
 * 
 * ICMP
 * 
 * Copyright (c) 2018 Friedrich Doku
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 or later as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details
 *
 */
#include <net/icmp.h>

using namespace DEOS;
using namespace DEOS::common;
using namespace DEOS::net;

 
InternetControlMessageProtocol::InternetControlMessageProtocol(InternetProtocolProvider* backend)
: InternetProtocolHandler(backend, 0x01)
{
}

InternetControlMessageProtocol::~InternetControlMessageProtocol()
{
}
            
void printf(char*);
void printfHex(uint8_t);
bool InternetControlMessageProtocol::OnInternetProtocolReceived(common::uint32_t srcIP_BE, common::uint32_t dstIP_BE,
                                            common::uint8_t* internetprotocolPayload, common::uint32_t size)
{
    if(size < sizeof(InternetControlMessageProtocolMessage))
        return false;
    
    InternetControlMessageProtocolMessage* msg = (InternetControlMessageProtocolMessage*)internetprotocolPayload;
    
    switch(msg->type)
    {
        
        case 0:
            printf("ping response from "); printfHex(srcIP_BE & 0xFF);
            printf("."); printfHex((srcIP_BE >> 8) & 0xFF);
            printf("."); printfHex((srcIP_BE >> 16) & 0xFF);
            printf("."); printfHex((srcIP_BE >> 24) & 0xFF);
            printf("\n");
            break;
            
        case 8:
            msg->type = 0;
            msg->checksum = 0;
            msg->checksum = InternetProtocolProvider::Checksum((uint16_t*)msg,
                sizeof(InternetControlMessageProtocolMessage));
            return true;
    }
    
    return false;
}

void InternetControlMessageProtocol::RequestEchoReply(uint32_t ip_be)
{
    InternetControlMessageProtocolMessage icmp;
    icmp.type = 8; // ping
    icmp.code = 0;
    icmp.data = 0x3713; // 1337
    icmp.checksum = 0;
    icmp.checksum = InternetProtocolProvider::Checksum((uint16_t*)&icmp,
        sizeof(InternetControlMessageProtocolMessage));
    
    InternetProtocolHandler::Send(ip_be, (uint8_t*)&icmp, sizeof(InternetControlMessageProtocolMessage));
}
