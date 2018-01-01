 /*
 * Created on Mon Jan 01 2018
 * Single-Chip 10/100 Mbps PCI Ethernet Controller with Integrated PHY 
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

#ifndef __DEOS__DRIVERS__AMD_AM79C973_H
#define __DEOS__DRIVERS__AMD_AM79C973_H


#include <common/types.h>
#include <drivers/driver.h>
#include <hardwarecommunication/pci.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/port.h>


namespace DEOS
{
    namespace drivers
    {
        
        class amd_am79c973;
        
        class RawDataHandler
        {
        protected:
            amd_am79c973* backend;
        public:
            RawDataHandler(amd_am79c973* backend);
            ~RawDataHandler();
            
            virtual bool OnRawDataReceived(common::uint8_t* buffer, common::uint32_t size);
            void Send(common::uint8_t* buffer, common::uint32_t size);
        };
        
        
        class amd_am79c973 : public Driver, public hardwarecommunication::InterruptHandler
        {
            struct InitializationBlock
            {
                common::uint16_t mode;
                unsigned reserved1 : 4;
                unsigned numSendBuffers : 4;
                unsigned reserved2 : 4;
                unsigned numRecvBuffers : 4;
                common::uint64_t physicalAddress : 48;
                common::uint16_t reserved3;
                common::uint64_t logicalAddress;
                common::uint32_t recvBufferDescrAddress;
                common::uint32_t sendBufferDescrAddress;
            } __attribute__((packed));
            
            
            struct BufferDescriptor
            {
                common::uint32_t address;
                common::uint32_t flags;
                common::uint32_t flags2;
                common::uint32_t avail;
            } __attribute__((packed));
            
            hardwarecommunication::Port16Bit MACAddress0Port;
            hardwarecommunication::Port16Bit MACAddress2Port;
            hardwarecommunication::Port16Bit MACAddress4Port;
            hardwarecommunication::Port16Bit registerDataPort;
            hardwarecommunication::Port16Bit registerAddressPort;
            hardwarecommunication::Port16Bit resetPort;
            hardwarecommunication::Port16Bit busControlRegisterDataPort;
            
            InitializationBlock initBlock;
            
            
            BufferDescriptor* sendBufferDescr;
            common::uint8_t sendBufferDescrMemory[2048+15];
            common::uint8_t sendBuffers[2*1024+15][8];
            common::uint8_t currentSendBuffer;
            
            BufferDescriptor* recvBufferDescr;
            common::uint8_t recvBufferDescrMemory[2048+15];
            common::uint8_t recvBuffers[2*1024+15][8];
            common::uint8_t currentRecvBuffer;
            
            
            RawDataHandler* handler;
            
        public:
            amd_am79c973(DEOS::hardwarecommunication::PeripheralComponentInterconnectDeviceDescriptor *dev,
                         DEOS::hardwarecommunication::InterruptManager* interrupts);
            ~amd_am79c973();
            
            void Activate();
            int Reset();
            common::uint32_t HandleInterrupt(common::uint32_t esp);
            
            void Send(common::uint8_t* buffer, int count);
            void Receive();
            
            void SetHandler(RawDataHandler* handler);
            common::uint64_t GetMACAddress();
            void SetIPAddress(common::uint32_t);
            common::uint32_t GetIPAddress();
        };
        
        
        
    }
}



#endif
