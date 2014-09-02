/**
 * Copyright 2014 Steven T Sell (ssell@ocularinteractive.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#ifndef __H__OCULAR_RENDERER_WINDOW__H__
#define __H__OCULAR_RENDERER_WINDOW__H__

#include <string>
#include "WindowDisplay.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    class RenderContext;

    /**
     * \class Window
     */
    class Window 
    {
    public:

        /**
         * \param name Display name of the window (default "Ocular Engine")
         * \param width Width of the window  (default 800)
         * \param height Height of the window (default 600)
         * \param colorBits Number of color bits (default 32)
         * \param depthBits Number of depth bits (default 32)
         * \param stencilBits Number of stencil bits (default 32)
         * \param display Display mode (default WINDOWED_BORDERED)
         */
        Window(std::string name = "Ocular Engine", 
               unsigned width = 800, 
               unsigned height = 600, 
               unsigned colorBits = 32,
               unsigned depthBits = 32, 
               unsigned stencilBits = 32, 
               WINDOW_DISPLAY_MODE display = WINDOWED_BORDERED);

        virtual ~Window();

        //--------------------------------------------

        /**
         * (Re)Creates the window with the provided attributes.
         */
        virtual void create() = 0;

        std::string getName() const;
        void setName(std::string name);

        unsigned getWidth() const;
        void setWidth(unsigned width);

        unsigned getHeight() const;
        void setHeight(unsigned height);

        unsigned getColorBits() const;
        void setColorBits(unsigned bits);

        unsigned getDepthBits() const;
        void setDepthBits(unsigned bits);

        unsigned getStencilBits() const;
        void setStencilBits(unsigned bits);

        WINDOW_DISPLAY_MODE getDisplayMode() const;
        void setDisplayMode(WINDOW_DISPLAY_MODE display);

    protected:
    
        RenderContext* m_pRenderContext;

        std::string m_Name;

        unsigned m_Width;
        unsigned m_Height;
        unsigned m_ColorBits;
        unsigned m_DepthBits;
        unsigned m_StencilBits;

        WINDOW_DISPLAY_MODE m_DisplayMode;

    private:
    };
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif