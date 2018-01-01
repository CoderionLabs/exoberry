/*
 * 
 * Widget
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
 */
#ifndef __DEOS__GUI__WIDGET_H
#define __DEOS__GUI__WIDGET_H


#include <common/types.h>
#include <common/graphicscontext.h>
#include <drivers/keyboard.h>

namespace DEOS
{
    namespace gui
    {
        
        class Widget : public DEOS::drivers::KeyboardEventHandler
        {
        protected:
            Widget* parent;
            common::int32_t x;
            common::int32_t y;
            common::int32_t w;
            common::int32_t h;
            
            common::uint8_t r;
            common::uint8_t g;
            common::uint8_t b;
            bool Focussable;

        public:

            Widget(Widget* parent,
                   common::int32_t x, common::int32_t y, common::int32_t w, common::int32_t h,
                   common::uint8_t r, common::uint8_t g, common::uint8_t b);
            ~Widget();
            
            virtual void GetFocus(Widget* widget);
            virtual void ModelToScreen(common::int32_t &x, common::int32_t& y);
            virtual bool ContainsCoordinate(common::int32_t x, common::int32_t y);
            
            virtual void Draw(common::GraphicsContext* gc);
            virtual void OnMouseDown(common::int32_t x, common::int32_t y, common::uint8_t button);
            virtual void OnMouseUp(common::int32_t x, common::int32_t y, common::uint8_t button);
            virtual void OnMouseMove(common::int32_t oldx, common::int32_t oldy, common::int32_t newx, common::int32_t newy);
        };
        
        
        class CompositeWidget : public Widget
        {
        private:
            Widget* children[100];
            int numChildren;
            Widget* focussedChild;
            
        public:
            CompositeWidget(Widget* parent,
                   common::int32_t x, common::int32_t y, common::int32_t w, common::int32_t h,
                   common::uint8_t r, common::uint8_t g, common::uint8_t b);
            ~CompositeWidget();            
            
            virtual void GetFocus(Widget* widget);
            virtual bool AddChild(Widget* child);
            
            virtual void Draw(common::GraphicsContext* gc);
            virtual void OnMouseDown(common::int32_t x, common::int32_t y, common::uint8_t button);
            virtual void OnMouseUp(common::int32_t x, common::int32_t y, common::uint8_t button);
            virtual void OnMouseMove(common::int32_t oldx, common::int32_t oldy, common::int32_t newx, common::int32_t newy);
            
            virtual void OnKeyDown(char);
            virtual void OnKeyUp(char);
        };
        
    }
}


#endif