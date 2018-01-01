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
#ifndef __DEOS__HARDWARECOMMUNICATION__PORT_H
#define __DEOS__HARDWARECOMMUNICATION__PORT_H

#include <common/types.h>

namespace DEOS
{
    namespace hardwarecommunication
    {

        class Port
        {
            protected:
                Port(DEOS::common::uint16_t portnumber);
                ~Port();
                DEOS::common::uint16_t portnumber;
        };

        class Port8Bit : public Port
        {
            public:
                Port8Bit(DEOS::common::uint16_t portnumber);
                ~Port8Bit();

                virtual DEOS::common::uint8_t Read();
                virtual void Write(DEOS::common::uint8_t data);

            protected:
                static inline DEOS::common::uint8_t Read8(DEOS::common::uint16_t _port)
                {
                    DEOS::common::uint8_t result;
                    __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }

                static inline void Write8(DEOS::common::uint16_t _port, DEOS::common::uint8_t _data)
                {
                    __asm__ volatile("outb %0, %1" : : "a" (_data), "Nd" (_port));
                }
        };

        class Port8BitSlow : public Port8Bit
        {
            public:
                Port8BitSlow(DEOS::common::uint16_t portnumber);
                ~Port8BitSlow();

                virtual void Write(DEOS::common::uint8_t data);
            protected:
                static inline void Write8Slow(DEOS::common::uint16_t _port, DEOS::common::uint8_t _data)
                {
                    __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (_data), "Nd" (_port));
                }

        };

        class Port16Bit : public Port
        {
            public:
                Port16Bit(DEOS::common::uint16_t portnumber);
                ~Port16Bit();

                virtual DEOS::common::uint16_t Read();
                virtual void Write(DEOS::common::uint16_t data);

            protected:
                static inline DEOS::common::uint16_t Read16(DEOS::common::uint16_t _port)
                {
                    DEOS::common::uint16_t result;
                    __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }

                static inline void Write16(DEOS::common::uint16_t _port, DEOS::common::uint16_t _data)
                {
                    __asm__ volatile("outw %0, %1" : : "a" (_data), "Nd" (_port));
                }
        };

        class Port32Bit : public Port
        {
            public:
                Port32Bit(DEOS::common::uint16_t portnumber);
                ~Port32Bit();

                virtual DEOS::common::uint32_t Read();
                virtual void Write(DEOS::common::uint32_t data);

            protected:
                static inline DEOS::common::uint32_t Read32(DEOS::common::uint16_t _port)
                {
                    DEOS::common::uint32_t result;
                    __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }

                static inline void Write32(DEOS::common::uint16_t _port, DEOS::common::uint32_t _data)
                {
                    __asm__ volatile("outl %0, %1" : : "a"(_data), "Nd" (_port));
                }
        };

    }
}


#endif
