/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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
#ifndef __H__OCULAR_EVENTS_MOUSE_SCROLL_INPUT_EVENT__H__
#define __H__OCULAR_EVENTS_MOUSE_SCROLL_INPUT_EVENT__H__

#include "Events/AEvent.hpp"
#include "Input/Keys.hpp"

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
         * \class MouseScrollInputEvent
         *
         * Event notifying of mouse scrolling input.
         *
         * String Descriptor: "MouseScrollInputEvent" <br/>
         * Event Priority: Medium 
         */
        class MouseScrollInputEvent : public AEvent 
        {
        public:

            MouseScrollInputEvent(int8_t delta);
            MouseScrollInputEvent();
                
            virtual ~MouseScrollInputEvent();

            int8_t delta;

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

//------------------------------------------------------------------------------------------

#endif