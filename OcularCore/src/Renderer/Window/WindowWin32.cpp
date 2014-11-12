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
#include "Renderer/Window/WindowWin32.hpp"
#include "OcularEngine.hpp"
#include "Events/Events/ShutdownEvent.hpp"
#include "Time/Timer.hpp"

#include <sstream>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // NON-CLASS METHODS
        //----------------------------------------------------------------------------------

        LRESULT CALLBACK WndProc(HWND const hwnd, UINT const msg, WPARAM const wp, LPARAM const lp)
        {
            WindowWin32* window = (WindowWin32*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

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

        WindowWin32::WindowWin32(std::string const name, unsigned const width, unsigned const height, unsigned const colorBits,
                                 unsigned const depthBits, unsigned const stencilBits, WINDOW_DISPLAY_MODE const display)
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

                // Setup our window to be later retrieved by WndProc
                // TODO: Will this cause errors with multiple windows? Need a different ID (GWLP_USERDATA - Window #)?
                SetWindowLongPtr(m_HWND, GWLP_USERDATA, (LONG)this);

                // Show the window
                ShowWindow(m_HWND, SW_SHOW);
                SetForegroundWindow(m_HWND);
                SetFocus(m_HWND);
            }
        }

        void WindowWin32::update(long long const time)
        {
            MSG message;

            Timer timer;
            timer.start();

            // Allow the message digestion time to process all new messages
            while(timer.getElapsedMS() < time)
            {
                if(GetMessage(&message, m_HWND, NULL, NULL) > 0)
                {
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                }
            }
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

        WNDCLASS WindowWin32::createWndClass(WNDPROC const wndProc)
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

        LRESULT CALLBACK WindowWin32::processMessage(HWND const hWnd, UINT const uMsg, WPARAM const wParam, LPARAM const lParam)
        {
            switch(uMsg)
            {
            case WM_DESTROY:
            case WM_CLOSE:
            case WM_QUIT:
                OcularEngine.EventManager()->queueEvent(std::make_shared<Ocular::Core::ShutdownEvent>());
                return 0;

            default:
                return DefWindowProc(hWnd, uMsg, wParam, lParam);
            }
        }
    }
}