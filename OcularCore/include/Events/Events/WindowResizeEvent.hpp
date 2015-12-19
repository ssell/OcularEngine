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

#pragma once
#ifndef __H__OCULAR_EVENTS_WINDOW_Resize_EVENT__H__
#define __H__OCULAR_EVENTS_WINDOW_Resize_EVENT__H__

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
        /**
         * \enum WindowResizeType
         * \brief Represents the type of resize event that occurred.
         */
        enum WindowResizeType
        {
            Resize = 0,     /// Matches WinAPI SIZE_RESTORED
            Minimized = 1,  /// Matches WinAPI SIZE_MINIMIZED
            Maximized = 2   /// Matches WinAPI SIZE_MAXIMIZED
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
             * Event Priority: Low 
             */
            class WindowResizeEvent : public AEvent 
            {
            public:

                WindowResizeEvent(std::shared_ptr<AWindow> pWindow, unsigned pWidth, unsigned pHeight, WindowResizeType pType);
                ~WindowResizeEvent();

                //----------------------------------------

                unsigned width;
                unsigned height;

                WindowResizeType type;

                std::shared_ptr<AWindow> window;

            protected:

            private:

                
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