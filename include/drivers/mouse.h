 /*
 * Created on Mon Jan 01 2018
 * 
 * Mouse Controller
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
#ifndef __DEOS__DRIVERS__MOUSE_H
#define __DEOS__DRIVERS__MOUSE_H

#include <common/types.h>
#include <hardwarecommunication/port.h>
#include <drivers/driver.h>
#include <hardwarecommunication/interrupts.h>

namespace DEOS
{
    namespace drivers
    {
    
        class MouseEventHandler
        {
        public:
            MouseEventHandler();

            virtual void OnActivate();
            virtual void OnMouseDown(DEOS::common::uint8_t button);
            virtual void OnMouseUp(DEOS::common::uint8_t button);
            virtual void OnMouseMove(int x, int y);
        };
        
        
        class MouseDriver : public DEOS::hardwarecommunication::InterruptHandler, public Driver
        {
            DEOS::hardwarecommunication::Port8Bit dataport;
            DEOS::hardwarecommunication::Port8Bit commandport;
            DEOS::common::uint8_t buffer[3];
            DEOS::common::uint8_t offset;
            DEOS::common::uint8_t buttons;

            MouseEventHandler* handler;
        public:
            MouseDriver(DEOS::hardwarecommunication::InterruptManager* manager, MouseEventHandler* handler);
            ~MouseDriver();
            virtual DEOS::common::uint32_t HandleInterrupt(DEOS::common::uint32_t esp);
            virtual void Activate();
        };

    }
}
    
#endif
