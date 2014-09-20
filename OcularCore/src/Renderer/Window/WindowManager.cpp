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
#include "Renderer\Window\WindowWin32.hpp"
#include "Exception.hpp"

#include <iostream>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
    
        WindowManager::WindowManager()
        {
    
        }

        WindowManager::~WindowManager()
        {
            destroyAllWindows();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        const AWindow* WindowManager::createWindow(std::string name, unsigned width, unsigned height,
            unsigned colorBits, unsigned depthBits, unsigned stencilBits, WINDOW_DISPLAY_MODE display)
        {
#ifdef OCULAR_WINDOWS
            return createWindowWin32(name, width, height, colorBits, depthBits, stencilBits, display);
#elif OCULAR_OSX
            return createWindowOSX(name, width, height, colorBits, depthBits, stencilBits, display);
#elif OCULAR_LINUX
            return createWindowLinux(name, width, height, colorBits, depthBits, stencilBits, display);
#endif
        }

        void WindowManager::destroyWindow(std::string name)
        {
            for(auto iter = m_Windows.begin(); iter != m_Windows.end(); iter++)
            {
                if((*iter).get()->getName().compare(name) == 0)
                {
                    // Close, release, and stop tracking the window

                    try 
                    {
                        (*iter).get()->close();    
                    }
                    catch(Exception e)
                    {
                        // TODO - Replace me
                        std::cout << e.getFile() << "@" << e.getLine() << ": " << e.getMessage();
                    }

                    (*iter).release();
                    m_Windows.erase(iter);

                    break;
                }
            }
        }

        void WindowManager::destroyAllWindows()
        {
            std::list<std::string> windows = listWindows();

            for(auto iter = windows.begin(); iter != windows.end(); iter++)
            {
                destroyWindow((*iter));
            }
        }

        std::list<std::string> WindowManager::listWindows()
        {
            std::list<std::string> windows;

            for(auto iter = m_Windows.begin(); iter != m_Windows.end(); iter++)
            {
                windows.push_back((*iter).get()->getName());
            }

            return windows;
        }

        const AWindow* WindowManager::getWindow(std::string name)
        {
            std::list<std::unique_ptr<AWindow>>::iterator iter;

            for(iter = m_Windows.begin(); iter != m_Windows.end(); iter++)
            {
                if((*iter).get()->getName().compare(name) == 0)
                {
                    return (*iter).get();
                }
            }

            return nullptr;
        }

        const AWindow* WindowManager::getMainWindow()
        {
            return getWindow(m_MainWindow);
        }

        void WindowManager::setMainWindow(std::string name)
        {
            m_MainWindow = name;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        const AWindow* WindowManager::createWindowWin32(std::string name, unsigned width, unsigned height,
            unsigned colorBits, unsigned depthBits, unsigned stencilBits, WINDOW_DISPLAY_MODE display)
        {
            AWindow* result = nullptr;

#ifdef OCULAR_WINDOWS
            try
            {
                m_Windows.push_front(std::make_unique<WindowWin32>(name, width, height, colorBits, depthBits, stencilBits, display));
                result = m_Windows.front().get();

                if(result != nullptr) 
                {
                    result->open();

                    if(m_MainWindow.empty()) 
                    {
                        m_MainWindow = result->getName();
                    }
                }
            } 
            catch(Exception& e)
            {
                // TODO - Replace me
                std::cout << e.getFile() << "@" << e.getLine() << ": " << e.getMessage();
            }
#endif

            return result;
        }

        const AWindow* WindowManager::createWindowOSX(std::string name, unsigned width, unsigned height,
            unsigned colorBits, unsigned depthBits, unsigned stencilBits, WINDOW_DISPLAY_MODE display)
        {
            AWindow* result = nullptr;

#ifdef OCULAR_OSX
            try
            {
                m_Windows.push_front(std::make_unique<Window>(
                    WindowOSX(name, width, height, colorBits, depthBits, stencilBits, display)));
                result = m_Windows.front().get();

                if(m_MainWindow.empty()) 
                {
                    m_MainWindow = result->getName();
                }
            } 
            catch(Exception& e)
            {
                // TODO - Replace me
                std::cout << e.getFile() << "@" << e.getLine() << ": " << e.getMessage();
            }
#endif

            return result;
        }

        const AWindow* WindowManager::createWindowLinux(std::string name, unsigned width, unsigned height,
            unsigned colorBits, unsigned depthBits, unsigned stencilBits, WINDOW_DISPLAY_MODE display)
        {
            AWindow* result = nullptr;

#ifdef OCULAR_LINUX
            try
            {
                m_Windows.push_front(std::make_unique<Window>(
                    WindowLinux(name, width, height, colorBits, depthBits, stencilBits, display)));
                result = m_Windows.front().get();

                if(m_MainWindow.empty()) 
                {
                    m_MainWindow = result->getName();
                }
            } 
            catch(Exception& e)
            {
                // TODO - Replace me
                std::cout << e.getFile() << "@" << e.getLine() << ": " << e.getMessage();
            }
#endif

            return result;
        }
    }
}