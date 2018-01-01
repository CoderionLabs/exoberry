 /*
 * Created on Mon Jan 01 2018
 * 
 * IPV4
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
#ifndef __DEOS__NET__IPV4_H
#define __DEOS__NET__IPV4_H

#include <common/types.h>
#include <net/etherframe.h>
#include <net/arp.h>

namespace DEOS
{
    namespace net
    {
        
        
        struct InternetProtocolV4Message
        {
            common::uint8_t headerLength : 4;
            common::uint8_t version : 4;
            common::uint8_t tos;
            common::uint16_t totalLength;
            
            common::uint16_t ident;
            common::uint16_t flagsAndOffset;
            
            common::uint8_t timeToLive;
            common::uint8_t protocol;
            common::uint16_t checksum;
            
            common::uint32_t srcIP;
            common::uint32_t dstIP;
        } __attribute__((packed));
        
        
        
        class InternetProtocolProvider;
     
        class InternetProtocolHandler
        {
        protected:
            InternetProtocolProvider* backend;
            common::uint8_t ip_protocol;
             
        public:
            InternetProtocolHandler(InternetProtocolProvider* backend, common::uint8_t protocol);
            ~InternetProtocolHandler();
            
            virtual bool OnInternetProtocolReceived(common::uint32_t srcIP_BE, common::uint32_t dstIP_BE,
                                            common::uint8_t* internetprotocolPayload, common::uint32_t size);
            void Send(common::uint32_t dstIP_BE, common::uint8_t* internetprotocolPayload, common::uint32_t size);
        };
     
     
        class InternetProtocolProvider : public EtherFrameHandler
        {
        friend class InternetProtocolHandler;
        protected:
            InternetProtocolHandler* handlers[255];
            AddressResolutionProtocol* arp;
            common::uint32_t gatewayIP;
            common::uint32_t subnetMask;
            
        public:
            InternetProtocolProvider(EtherFrameProvider* backend, 
                                     AddressResolutionProtocol* arp,
                                     common::uint32_t gatewayIP, common::uint32_t subnetMask);
            ~InternetProtocolProvider();
            
            bool OnEtherFrameReceived(common::uint8_t* etherframePayload, common::uint32_t size);

            void Send(common::uint32_t dstIP_BE, common::uint8_t protocol, common::uint8_t* buffer, common::uint32_t size);
            
            static common::uint16_t Checksum(common::uint16_t* data, common::uint32_t lengthInBytes);
        };
    }
}


#endif
