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
#ifndef __H__OCULAR_RENDERER_WIN_WINDOW__H__
#define __H__OCULAR_RENDERER_WIN_WINDOW__H__

#include "Definitions.hpp"
#include "Window.hpp"

#ifdef OCULAR_WINDOWS
#include <Windows.h>

/**
 * \addtogroup Ocular
 * @{ 
 */
namespace Ocular
{
    class Window_WIN : public Window 
    {
    public:

        Window_WIN(std::string name = "Ocular Engine", 
               unsigned width = 800, 
               unsigned height = 600, 
               unsigned colorBits = 32,
               unsigned depthBits = 32, 
               unsigned stencilBits = 32, 
               WINDOW_DISPLAY_MODE display = WINDOWED_BORDERED);

        ~Window_WIN();

        void create();

        HWND getHWND() const;
        HINSTANCE getHINSTANCE() const;

    protected:

    private:

        HWND      m_hWnd;
        HINSTANCE m_hInstance;
    };
}
/** 
 * }@ End of Doxygen Groups 
 */

#endif // OCULAR_WINDOWS
#endif // __H__OCULAR_RENDERER_WIN_WINDOW__H__