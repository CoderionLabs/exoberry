 /*
 * Created on Mon Jan 01 2018
 * 
 * ATA standard for connecting and transferring data from hard disk drives
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
#ifndef __DEOS__DRIVERS__ATA_H
#define __DEOS__DRIVERS__ATA_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/port.h>

namespace DEOS
{
    namespace drivers
    {
        
        class AdvancedTechnologyAttachment
        {
        protected:
            bool master;
            hardwarecommunication::Port16Bit dataPort;
            hardwarecommunication::Port8Bit errorPort;
            hardwarecommunication::Port8Bit sectorCountPort;
            hardwarecommunication::Port8Bit lbaLowPort;
            hardwarecommunication::Port8Bit lbaMidPort;
            hardwarecommunication::Port8Bit lbaHiPort;
            hardwarecommunication::Port8Bit devicePort;
            hardwarecommunication::Port8Bit commandPort;
            hardwarecommunication::Port8Bit controlPort;
        public:
            
            AdvancedTechnologyAttachment(bool master, common::uint16_t portBase);
            ~AdvancedTechnologyAttachment();
            
            void Identify();
            void Read28(common::uint32_t sectorNum, int count = 512);
            void Write28(common::uint32_t sectorNum, common::uint8_t* data, common::uint32_t count);
            void Flush();
            
            
        };
        
    }
}

#endif
