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
    //--------------------------------------------------------------------------------------
    // CONSTRUCTORS
    //--------------------------------------------------------------------------------------

    Window::Window(std::string name, unsigned width, unsigned height, unsigned colorBits,
                   unsigned depthBits, unsigned stencilBits, WINDOW_DISPLAY_MODE display)
    {
        m_Name = name;
        m_Width = width;
        m_Height = height;
        m_ColorBits = colorBits;
        m_DepthBits = depthBits;
        m_StencilBits = stencilBits;
    }

    Window::~Window()
    {
        if(m_pRenderContext != nullptr)
        {
            delete m_pRenderContext;
            m_pRenderContext = nullptr;
        }
    }

    //--------------------------------------------------------------------------------------
    // PUBLIC METHODS
    //--------------------------------------------------------------------------------------

    std::string Window::getName() const
    {
        return m_Name;
    }

    void Window::setName(std::string name) 
    {
        m_Name = name;
    }

    unsigned Window::getWidth() const 
    {
        return m_Width;
    }

    void Window::setWidth(unsigned width) 
    {
        m_Width = width;
    }

    unsigned Window::getHeight() const 
    {
        return m_Height;
    }

    void Window::setHeight(unsigned height)  
    {
        m_Height = height;
    }

    unsigned Window::getColorBits() const 
    {
        return m_ColorBits;
    }

    void Window::setColorBits(unsigned bits) 
    {
        m_ColorBits = bits;
    }

    unsigned Window::getDepthBits() const 
    {
        return m_DepthBits;
    }

    void Window::setDepthBits(unsigned bits) 
    {
        m_DepthBits = bits;
    }

    unsigned Window::getStencilBits() const 
    {
        return m_StencilBits;
    }

    void Window::setStencilBits(unsigned bits) 
    {
        m_StencilBits = bits;
    }

    WINDOW_DISPLAY_MODE Window::getDisplayMode() const
    {
        return m_DisplayMode;
    }

    void Window::setDisplayMode(WINDOW_DISPLAY_MODE display) 
    {
        m_DisplayMode = display;
    }

    //--------------------------------------------------------------------------------------
    // PROTECTED METHODS
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    // PRIVATE METHODS
    //--------------------------------------------------------------------------------------
}