 /*
 * Created on Mon Jan 01 2018
 * 
 * System Call Manager
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
#ifndef __DEOS__SYSCALLS_H
#define __DEOS__SYSCALLS_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <multitasking.h>

namespace DEOS
{
    
    class SyscallHandler : public hardwarecommunication::InterruptHandler
    {
        
    public:
        SyscallHandler(hardwarecommunication::InterruptManager* interruptManager, DEOS::common::uint8_t InterruptNumber);
        ~SyscallHandler();
        
        virtual DEOS::common::uint32_t HandleInterrupt(DEOS::common::uint32_t esp);

    };
}


#endif