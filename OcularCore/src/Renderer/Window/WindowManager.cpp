/**
 * Copyright 2014-2015 Steven T Sell (ssell@ocularinteractive.com)
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
#include "Exceptions/Exception.hpp"
#include "OcularEngine.hpp"

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
            m_MainWindow = nullptr;
        }

        WindowManager::~WindowManager()
        {
            closeAllWindows();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        std::shared_ptr<AWindow> WindowManager::openWindow(WindowDescriptor const descriptor)
        {
#ifdef OCULAR_WINDOWS
            return openWindowWin32(descriptor);
#elif OCULAR_OSX
            return openWindowOSX(descriptor);
#elif OCULAR_LINUX
            return openWindowLinux(descriptor);
#endif
        }

        void WindowManager::closeWindow(UUID const& uuid)
        {
            bool needNewMainWindow = false;

            if((m_MainWindow != nullptr) && (m_MainWindow->getUUID() == uuid))
            {
                // We are deleting the main window, set it to next available window when done
                needNewMainWindow = true;
            }

            //----------------------------------------

            for(auto iter = m_Windows.begin(); iter != m_Windows.end(); ++iter)
            {
                if((*iter)->getUUID() == uuid)
                {
                    //--------------------------------
                    // Close, release, and stop tracking the window

                    try 
                    {
                        (*iter).get()->close();    
                    }
                    catch(Exception e)
                    {
                        OcularEngine.Logger()->error(e);
                    }

                    (*iter) = nullptr;
                    m_Windows.erase(iter);

                    break;
                }
            }

            //----------------------------------------

            if(needNewMainWindow)
            {
                if(m_Windows.size() > 0)
                {
                    m_MainWindow = m_Windows.front();
                }
                else 
                {
                    m_MainWindow = nullptr;
                }
            }
        }

        void WindowManager::closeAllWindows()
        {
            while(m_Windows.size() > 0)
            {
                closeWindow(m_Windows.front()->getUUID());
            }
        }

        std::list<std::shared_ptr<AWindow>> WindowManager::listWindows() const
        {
            return m_Windows;
        }

        unsigned WindowManager::getNumWindows() const
        {
            return m_Windows.size();
        }

        std::shared_ptr<AWindow> WindowManager::getWindow(UUID const& uuid)
        {
            std::list<std::shared_ptr<AWindow>>::iterator iter;

            for(iter = m_Windows.begin(); iter != m_Windows.end(); iter++)
            {
                if((*iter)->getUUID() == uuid)
                {
                    return (*iter);
                }
            }

            return nullptr;
        }

        std::shared_ptr<AWindow> WindowManager::getMainWindow()
        {
            return m_MainWindow;
        }

        void WindowManager::setMainWindow(UUID const& uuid)
        {
            m_MainWindow = getWindow(uuid);
        }
        
        void WindowManager::updateWindows(long long time)
        {
            for(auto iter = m_Windows.begin(); iter != m_Windows.end(); ++iter)
            {
                (*iter)->update(time);
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        std::shared_ptr<AWindow> WindowManager::openWindowWin32(WindowDescriptor const descriptor)
        {
            std::shared_ptr<AWindow> result;

#ifdef OCULAR_WINDOWS
            try
            {
                m_Windows.push_front(std::make_shared<WindowWin32>(descriptor));
                result = m_Windows.front();

                if(result != nullptr) 
                {
                    result->open();

                    if(m_MainWindow == nullptr)
                    {
                        m_MainWindow = result;
                    }
                }
            } 
            catch(Exception& e)
            {
                OcularEngine.Logger()->error(e);
            }
#endif

            return result;
        }

        std::shared_ptr<AWindow> WindowManager::openWindowOSX(WindowDescriptor const descriptor)
        {
            std::shared_ptr<AWindow> result = nullptr;

#ifdef OCULAR_OSX
            try
            {
                m_Windows.push_front(std::make_unique<Window>(WindowOSX(descriptor)));
                result = m_Windows.front().get();

                if(m_MainWindow == nullptr)
                {
                    m_MainWindow = result;
                }
            } 
            catch(Exception& e)
            {
                OcularEngine.Logger()->error(e);
            }
#endif

            return result;
        }

        std::shared_ptr<AWindow> WindowManager::openWindowLinux(WindowDescriptor const descriptor)
        {
            std::shared_ptr<AWindow> result = nullptr;

#ifdef OCULAR_LINUX
            try
            {
                m_Windows.push_front(std::make_unique<Window>(WindowLinux(descriptor)));
                result = m_Windows.front().get();

                if(m_MainWindow == nullptr)
                {
                    m_MainWindow = result;
                }
            } 
            catch(Exception& e)
            {
                OcularEngine.Logger()->error(e);
            }
#endif

            return result;
        }
    }
}