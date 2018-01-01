 /*
 * Created on Mon Jan 01 2018
 * 
 * Keyboard controller
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
#ifndef __DEOS__DRIVERS__KEYBOARD_H
#define __DEOS__DRIVERS__KEYBOARD_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>
#include <hardwarecommunication/port.h>

namespace DEOS
{
    namespace drivers
    {
    
        struct KeyboardEventHandler
        {
            KeyboardEventHandler();

            virtual void OnKeyDown(char);
            virtual void OnKeyUp(char);
        };
        
        class KeyboardDriver : public DEOS::hardwarecommunication::InterruptHandler, public Driver
        {
            DEOS::hardwarecommunication::Port8Bit dataport;
            DEOS::hardwarecommunication::Port8Bit commandport;
            
            KeyboardEventHandler* handler;
        public:
            KeyboardDriver(DEOS::hardwarecommunication::InterruptManager* manager, KeyboardEventHandler *handler);
            ~KeyboardDriver();
            virtual DEOS::common::uint32_t HandleInterrupt(DEOS::common::uint32_t esp);
            virtual void Activate();
        };

    }
}
    
#endif