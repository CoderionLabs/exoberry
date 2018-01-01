 /*
 * Created on Mon Jan 01 2018
 * 
 * Global Descriptor Table
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
#ifndef __DEOS__GDT_H
#define __DEOS__GDT_H

#include <common/types.h>

namespace DEOS
{
    
    class GlobalDescriptorTable
    {
        public:

            class SegmentDescriptor
            {
                private:
                    DEOS::common::uint16_t limit_lo;
                    DEOS::common::uint16_t base_lo;
                    DEOS::common::uint8_t base_hi;
                    DEOS::common::uint8_t type;
                    DEOS::common::uint8_t limit_hi;
                    DEOS::common::uint8_t base_vhi;

                public:
                    SegmentDescriptor(DEOS::common::uint32_t base, DEOS::common::uint32_t limit, DEOS::common::uint8_t type);
                    DEOS::common::uint32_t Base();
                    DEOS::common::uint32_t Limit();
            } __attribute__((packed));

        private:
            SegmentDescriptor nullSegmentSelector;
            SegmentDescriptor unusedSegmentSelector;
            SegmentDescriptor codeSegmentSelector;
            SegmentDescriptor dataSegmentSelector;

        public:
            GlobalDescriptorTable();
            ~GlobalDescriptorTable();

            DEOS::common::uint16_t CodeSegmentSelector();
            DEOS::common::uint16_t DataSegmentSelector();
    };

}
    
#endif