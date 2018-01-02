 
 /*
 * Created on Mon Jan 01 2018
 * 
 * Driver manager
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
#ifndef __DEOS__DRIVERS__DRIVER_H
#define __DEOS__DRIVERS__DRIVER_H

namespace DEOS
{
    namespace drivers
    {

        class Driver
        {
        public:
            Driver();
            ~Driver();            
            virtual void Activate();
            virtual int Reset();
            virtual void Deactivate();
        };

        class DriverManager
        {
        public:
            Driver* drivers[265];
            int numDrivers;
            
        public:
            DriverManager();
            void AddDriver(Driver*);
            
            void ActivateAll();
        };
        
    }
}
    
    
#endif