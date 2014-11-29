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

#include "Renderer\Window\Window.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        AWindow::AWindow(std::string const name, unsigned const width, unsigned const height, unsigned const colorBits,
                         unsigned const depthBits, unsigned const stencilBits, WINDOW_DISPLAY_MODE const display, bool alwaysOnTop)
        {
            m_Name = name;
            m_Width = width;
            m_Height = height;
            m_ColorBits = colorBits;
            m_DepthBits = depthBits;
            m_StencilBits = stencilBits;
            m_DisplayMode = display;
            m_RenderExclusive = alwaysOnTop;
        }

        AWindow::~AWindow()
        {
          
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        std::string AWindow::getName() const
        {
            return m_Name;
        }

        void AWindow::setName(std::string const name)
        {
            m_Name = name;
        }

        unsigned AWindow::getResolutionX() const
        {
            return m_Width;
        }

        void AWindow::setResolutionX(unsigned const width)
        {
            m_Width = width;
        }

        unsigned AWindow::getResolutionY() const
        {
            return m_Height;
        }

        void AWindow::setResolutionY(unsigned const height)
        {
            m_Height = height;
        }

        unsigned AWindow::getColorBits() const
        {
            return m_ColorBits;
        }

        void AWindow::setColorBits(unsigned const bits)
        {
            m_ColorBits = bits;
        }

        unsigned AWindow::getDepthBits() const
        {
            return m_DepthBits;
        }

        void AWindow::setDepthBits(unsigned const bits)
        {
            m_DepthBits = bits;
        }

        unsigned AWindow::getStencilBits() const
        {
            return m_StencilBits;
        }

        void AWindow::setStencilBits(unsigned const bits)
        {
            m_StencilBits = bits;
        }

        WINDOW_DISPLAY_MODE AWindow::getDisplayMode() const
        {
            return m_DisplayMode;
        }

        void AWindow::setDisplayMode(WINDOW_DISPLAY_MODE const display)
        {
            m_DisplayMode = display;
        }

        bool AWindow::getIsAlwaysOnTop() const
        {
            return m_RenderExclusive;
        }

        void AWindow::setIsAlwaysOnTop(bool const onTop) 
        {
            m_RenderExclusive = onTop;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}