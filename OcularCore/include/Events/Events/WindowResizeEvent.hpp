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
#ifndef __H__OCULAR_EVENTS_WINDOW_RESIZE_EVENT__H__
#define __H__OCULAR_EVENTS_WINDOW_RESIZE_EVENT__H__

#include "Events/AEvent.hpp"
#include "Renderer/Window/Window.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        enum WINDOW_RESIZE_TYPE
        {
            RESIZE = 0,     /// Matches WinAPI SIZE_RESTORED
            MINIMIZED = 1,  /// Matches WinAPI SIZE_MINIMIZED
            MAXIMIZED = 2   /// Matches WinAPI SIZE_MAXIMIZED
        };

        /**
         * \addtogroup Events
         * @{
         */
        namespace Events
        {
            /**
             * \class WindowResizeEvent
             *
             * Event notifying of a window resize. <br/>
             * This event contains the following additional information: <br/>
             *
             * <ul>
             *     <li>Pointer to Window that was resized</li>
             *     <li>New Window width</li>
             *     <li>New Window height</li>
             *     <li>Type of resize event (normal resize, maximize, minimize)</li>
             * </ul><br/>
             *
             * String Descriptor: "WindowResizeEvent" <br/>
             * Event Priority: LOW 
             */
            class WindowResizeEvent : public AEvent 
            {
            public:

                WindowResizeEvent(std::shared_ptr<AWindow> window, unsigned width, unsigned height, WINDOW_RESIZE_TYPE type);
                ~WindowResizeEvent();

                //----------------------------------------

                WINDOW_RESIZE_TYPE getResizeType() const;

                unsigned getNewWidth() const;
                unsigned getNewHeight() const;

                std::shared_ptr<AWindow> getWindow() const;

            protected:

            private:

                std::shared_ptr<AWindow> m_pWindow;
            
                unsigned m_NewWidth;
                unsigned m_NewHeight;

                WINDOW_RESIZE_TYPE m_Type;
            };
        }
        /**
         * @} End of Doxygen Groups
         */
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif