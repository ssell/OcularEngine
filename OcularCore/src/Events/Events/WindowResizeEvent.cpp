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

#include "Events/Events/WindowResizeEvent.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        namespace Events
        {
            //------------------------------------------------------------------------------
            // CONSTRUCTORS
            //------------------------------------------------------------------------------

            WindowResizeEvent::WindowResizeEvent(
                std::shared_ptr<AWindow> window, unsigned const width, unsigned const height, WindowResizeType const type)
                : AEvent("WindowResizeEvent", Priority::Low)
            {
                m_pWindow = window;
                m_NewWidth = width;
                m_NewHeight = height;
                m_Type = type;
            }

            WindowResizeEvent::~WindowResizeEvent()
            {
                m_pWindow = nullptr;
            }

            //------------------------------------------------------------------------------
            // PUBLIC METHODS
            //------------------------------------------------------------------------------

            WindowResizeType WindowResizeEvent::getResizeType() const
            {
                return m_Type;
            }

            unsigned WindowResizeEvent::getNewWidth() const 
            {
                return m_NewWidth;
            }

            unsigned WindowResizeEvent::getNewHeight() const
            {
                return m_NewHeight;
            }

            std::shared_ptr<AWindow> WindowResizeEvent::getWindow() const 
            {
                return m_pWindow;
            }

            //------------------------------------------------------------------------------
            // PROTECTED METHODS
            //------------------------------------------------------------------------------

            //------------------------------------------------------------------------------
            // PRIVATE METHODS
            //------------------------------------------------------------------------------
        }
    }
}