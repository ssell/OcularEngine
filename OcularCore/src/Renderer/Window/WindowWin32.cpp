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

#include "Exception.hpp"
#include "Renderer\Window\WindowWin32.hpp"

#include <sstream>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // NON-CLASS METHODS
        //----------------------------------------------------------------------------------

        LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wp, LPARAM lp )
        {
            WindowWin32* window = (WindowWin32*)GetWindowLong(hwnd, GWL_USERDATA);

            if(window != nullptr)
            {
                return window->processMessage(hwnd, msg, wp, lp);
            }
            else 
            {
                return DefWindowProc(hwnd, msg, wp, lp);
            }
        }

        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        WindowWin32::WindowWin32(std::string name, unsigned width, unsigned height, unsigned colorBits,
            unsigned depthBits, unsigned stencilBits, WINDOW_DISPLAY_MODE display)
            : AWindow(name, width, height, colorBits, depthBits, stencilBits, display)
        {
            m_HINSTANCE = nullptr;
            m_HWND = nullptr;
        }

        WindowWin32::~WindowWin32() 
        {
            if(m_HWND != nullptr)
            {
                DestroyWindow(m_HWND);
                UnregisterClass(TEXT(m_Name.c_str()), m_HINSTANCE);

                m_HWND = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void WindowWin32::open()
        {
            if(m_HWND == nullptr)
            {
                m_HINSTANCE = GetModuleHandle(NULL);

                if(m_HINSTANCE == nullptr)
                {
                    DWORD error = GetLastError();
                    std::stringstream stream;
                    stream << "Failed to get HINSTANCE [WinApi error " << error << "]";

                    THROW_EXCEPTION(stream.str());
                }

                RECT windowRect = createWindowRect();
                WNDCLASS windowClass = createWndClass((WNDPROC)WndProc);

                RegisterClass(&windowClass);

                m_HWND = CreateWindow(TEXT(m_Name.c_str()),
                                      TEXT(m_Name.c_str()),
                                      WS_OVERLAPPEDWINDOW,
                                      CW_USEDEFAULT,
                                      0,
                                      CW_USEDEFAULT,
                                      0,
                                      0,
                                      0,
                                      m_HINSTANCE,
                                      this);

                if(m_HWND == nullptr) 
                {
                    DWORD error = GetLastError();
                    std::stringstream stream;
                    stream << "Failed to create window [WinApi error " << error << "]";

                    THROW_EXCEPTION(stream.str());
                }

                ShowWindow(m_HWND, SW_SHOW);
                SetForegroundWindow(m_HWND);
                SetFocus(m_HWND);
            }
        }

        void WindowWin32::update()
        {
            // TODO? Just a close -> open, or something more?
        }

        void WindowWin32::close()
        {
            if(m_HWND != nullptr)
            {
                if(!DestroyWindow(m_HWND))
                {
                    DWORD error = GetLastError();
                    std::stringstream stream;
                    stream << "Failed to destroy window handle '" << m_HWND
                           << "' [WinApi error " << error << "]";

                    THROW_EXCEPTION(stream.str());
                }

                m_HWND = nullptr;
            }

            if(!UnregisterClass(TEXT(m_Name.c_str()), m_HINSTANCE))
            {
                DWORD error = GetLastError();
                std::stringstream stream;
                stream << "Failed to unregister class '" << m_Name 
                       << "' [WinApi error " << error << "]";

                THROW_EXCEPTION(stream.str());
            }
        }

        HWND WindowWin32::getHWND() const
        {
            return m_HWND;
        }

        HINSTANCE WindowWin32::getHINSTANCE() const 
        {
            return m_HINSTANCE;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

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

            return windowClass;
        }

        LRESULT CALLBACK WindowWin32::processMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            // TODO - Integrate me with future event system

            switch(uMsg)
            {
            case WM_DESTROY:
            case WM_CLOSE:
                PostQuitMessage(0);
                return 0;

            default:
                return DefWindowProc(hWnd, uMsg, wParam, lParam);
            }
        }
    }
}