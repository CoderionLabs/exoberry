/*
 * Created on Mon Jan 01 2018
 * 
 * PCI Controller
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
#ifndef __DEOS__HARDWARECOMMUNICATION__PCI_H
#define __DEOS__HARDWARECOMMUNICATION__PCI_H

#include <hardwarecommunication/port.h>
#include <drivers/driver.h>
#include <common/types.h>
#include <hardwarecommunication/interrupts.h>

#include <memorymanagement.h>

namespace DEOS
{
    namespace hardwarecommunication
    {

        enum BaseAddressRegisterType
        {
            MemoryMapping = 0,
            InputOutput = 1
        };
        
        class BaseAddressRegister
        {
        public:
            bool prefetchable;
            DEOS::common::uint8_t* address;
            DEOS::common::uint32_t size;
            BaseAddressRegisterType type;
        };
        
        class PeripheralComponentInterconnectDeviceDescriptor
        {
        public:
            DEOS::common::uint32_t portBase;
            DEOS::common::uint32_t interrupt;
            
            DEOS::common::uint16_t bus;
            DEOS::common::uint16_t device;
            DEOS::common::uint16_t function;

            DEOS::common::uint16_t vendor_id;
            DEOS::common::uint16_t device_id;
            
            DEOS::common::uint8_t class_id;
            DEOS::common::uint8_t subclass_id;
            DEOS::common::uint8_t interface_id;

            DEOS::common::uint8_t revision;
            
            PeripheralComponentInterconnectDeviceDescriptor();
            ~PeripheralComponentInterconnectDeviceDescriptor();
            
        };

        class PeripheralComponentInterconnectController
        {
            Port32Bit dataPort;
            Port32Bit commandPort;
            
        public:
            PeripheralComponentInterconnectController();
            ~PeripheralComponentInterconnectController();
            
            DEOS::common::uint32_t Read(DEOS::common::uint16_t bus, DEOS::common::uint16_t device,
             DEOS::common::uint16_t function, DEOS::common::uint32_t registeroffset);
             
            void Write(DEOS::common::uint16_t bus, DEOS::common::uint16_t device,
             DEOS::common::uint16_t function, DEOS::common::uint32_t registeroffset, DEOS::common::uint32_t value);

            bool DeviceHasFunctions(DEOS::common::uint16_t bus, DEOS::common::uint16_t device);
            
            void SelectDrivers(DEOS::drivers::DriverManager* driverManager,
             DEOS::hardwarecommunication::InterruptManager* interrupts);

            DEOS::drivers::Driver* GetDriver(PeripheralComponentInterconnectDeviceDescriptor dev
            , DEOS::hardwarecommunication::InterruptManager* interrupts);

            PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(DEOS::common::uint16_t bus,
             DEOS::common::uint16_t device, DEOS::common::uint16_t function);

            BaseAddressRegister GetBaseAddressRegister(DEOS::common::uint16_t bus, DEOS::common::uint16_t device,
             DEOS::common::uint16_t function, DEOS::common::uint16_t bar);
        };

    }
}
    
#endif