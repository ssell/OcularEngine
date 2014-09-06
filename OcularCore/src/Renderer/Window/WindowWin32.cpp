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

#include "Renderer\Window\WindowWin32.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    //--------------------------------------------------------------------------------------
    // CONSTRUCTORS
    //--------------------------------------------------------------------------------------

    WindowWin32::WindowWin32(std::string name, unsigned width, unsigned height, unsigned colorBits,
        unsigned depthBits, unsigned stencilBits, WINDOW_DISPLAY_MODE display)
        : Window(name, width, height, colorBits, depthBits, stencilBits, display)
    {
    
    }

    WindowWin32::~WindowWin32() 
    {
    
    }

    //--------------------------------------------------------------------------------------
    // PUBLIC METHODS
    //--------------------------------------------------------------------------------------

    void WindowWin32::open() 
    {
    
    }

    void WindowWin32::update()
    {
    
    }

    void WindowWin32::close()
    {
    
    }

    HWND WindowWin32::getHWND() const
    {
        return m_HWND;
    }

    HINSTANCE WindowWin32::getHINSTANCE() const 
    {
        return m_HINSTANCE;
    }

    //--------------------------------------------------------------------------------------
    // PROTECTED METHODS
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    // PRIVATE METHODS
    //--------------------------------------------------------------------------------------

    RECT WindowWin32::createWindowRect()
    {
        RECT windowRect;

        windowRect.left   = 0L;
        windowRect.right  = static_cast<long>(m_Width);
        windowRect.top    = 0L;
        windowRect.bottom = static_cast<long>(m_Height);

        return windowRect;
    }

    WNDCLASS WindowWin32::createWndClass(WNDPROC wndProc)
    {
        WNDCLASS windowClass;

        windowClass.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        windowClass.lpfnWndProc   = wndProc;
        windowClass.cbClsExtra    = 0;
        windowClass.cbWndExtra    = sizeof(WindowWin32*);
        windowClass.hInstance     = m_HINSTANCE;
        windowClass.hIcon         = LoadIcon(NULL, IDI_WINLOGO); // TODO
        windowClass.hCursor       = LoadIcon(NULL, IDC_ARROW);   // TODO
        windowClass.hbrBackground = NULL;
        windowClass.lpszMenuName  = NULL;
        windowClass.lpszClassName = TEXT(m_Name.c_str());
    }

    LRESULT CALLBACK WindowWin32::processMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
    
    }
}