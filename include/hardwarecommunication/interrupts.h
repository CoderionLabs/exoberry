 /*
 * Created on Mon Jan 01 2018
 * 
 * Interrupts
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
#ifndef __DEOS__HARDWARECOMMUNICATION__INTERRUPTMANAGER_H
#define __DEOS__HARDWARECOMMUNICATION__INTERRUPTMANAGER_H

#include <gdt.h>
#include <multitasking.h>
#include <common/types.h>
#include <hardwarecommunication/port.h>


namespace DEOS
{
    namespace hardwarecommunication
    {

        class InterruptManager;

        class InterruptHandler
        {
        protected:
            DEOS::common::uint8_t InterruptNumber;
            InterruptManager* interruptManager;
            InterruptHandler(InterruptManager* interruptManager, DEOS::common::uint8_t InterruptNumber);
            ~InterruptHandler();
        public:
            virtual DEOS::common::uint32_t HandleInterrupt(DEOS::common::uint32_t esp);
        };


        class InterruptManager
        {
            friend class InterruptHandler;
            protected:

                static InterruptManager* ActiveInterruptManager;
                InterruptHandler* handlers[256];
                TaskManager *taskManager;

                struct GateDescriptor
                {
                    DEOS::common::uint16_t handlerAddressLowBits;
                    DEOS::common::uint16_t gdt_codeSegmentSelector;
                    DEOS::common::uint8_t reserved;
                    DEOS::common::uint8_t access;
                    DEOS::common::uint16_t handlerAddressHighBits;
                } __attribute__((packed));

                static GateDescriptor interruptDescriptorTable[256];

                struct InterruptDescriptorTablePointer
                {
                    DEOS::common::uint16_t size;
                    DEOS::common::uint32_t base;
                } __attribute__((packed));

                DEOS::common::uint16_t hardwareInterruptOffset;
                static void SetInterruptDescriptorTableEntry(DEOS::common::uint8_t interrupt,
                    DEOS::common::uint16_t codeSegmentSelectorOffset, void (*handler)(),
                    DEOS::common::uint8_t DescriptorPrivilegeLevel, DEOS::common::uint8_t DescriptorType);


                static void InterruptIgnore();

                static void HandleInterruptRequest0x00();
                static void HandleInterruptRequest0x01();
                static void HandleInterruptRequest0x02();
                static void HandleInterruptRequest0x03();
                static void HandleInterruptRequest0x04();
                static void HandleInterruptRequest0x05();
                static void HandleInterruptRequest0x06();
                static void HandleInterruptRequest0x07();
                static void HandleInterruptRequest0x08();
                static void HandleInterruptRequest0x09();
                static void HandleInterruptRequest0x0A();
                static void HandleInterruptRequest0x0B();
                static void HandleInterruptRequest0x0C();
                static void HandleInterruptRequest0x0D();
                static void HandleInterruptRequest0x0E();
                static void HandleInterruptRequest0x0F();
                static void HandleInterruptRequest0x31();

                static void HandleInterruptRequest0x80();

                static void HandleException0x00();
                static void HandleException0x01();
                static void HandleException0x02();
                static void HandleException0x03();
                static void HandleException0x04();
                static void HandleException0x05();
                static void HandleException0x06();
                static void HandleException0x07();
                static void HandleException0x08();
                static void HandleException0x09();
                static void HandleException0x0A();
                static void HandleException0x0B();
                static void HandleException0x0C();
                static void HandleException0x0D();
                static void HandleException0x0E();
                static void HandleException0x0F();
                static void HandleException0x10();
                static void HandleException0x11();
                static void HandleException0x12();
                static void HandleException0x13();
                
                static DEOS::common::uint32_t HandleInterrupt(DEOS::common::uint8_t interrupt, DEOS::common::uint32_t esp);
                DEOS::common::uint32_t DoHandleInterrupt(DEOS::common::uint8_t interrupt, DEOS::common::uint32_t esp);

                Port8BitSlow programmableInterruptControllerMasterCommandPort;
                Port8BitSlow programmableInterruptControllerMasterDataPort;
                Port8BitSlow programmableInterruptControllerSlaveCommandPort;
                Port8BitSlow programmableInterruptControllerSlaveDataPort;

            public:
                InterruptManager(DEOS::common::uint16_t hardwareInterruptOffset, DEOS::GlobalDescriptorTable* globalDescriptorTable, DEOS::TaskManager* taskManager);
                ~InterruptManager();
                DEOS::common::uint16_t HardwareInterruptOffset();
                void Activate();
                void Deactivate();
        };
        
    }
}

#endif