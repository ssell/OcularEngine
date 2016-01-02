/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
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
#ifndef __H__OCULAR_EVENTS_MOUSE_MOVE_INPUT_EVENT__H__
#define __H__OCULAR_EVENTS_MOUSE_MOVE_INPUT_EVENT__H__

#include "Events/AEvent.hpp"
#include "Input/Keys.hpp"
#include "Math/Vector2.hpp"

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
         * \addtogroup Events
         * @{
         */
        namespace Events
        {
            /**
             * \class MouseMoveInputEvent
             *
             * Event notifying of mouse movement input.
             *
             * String Descriptor: "MouseMoveInputEvent" <br/>
             * Event Priority: Medium 
             */
            class MouseMoveInputEvent : public AEvent 
            {
            public:

                MouseMoveInputEvent(Math::Vector2i const& prev, Math::Vector2i const& curr);
                MouseMoveInputEvent();
                ~MouseMoveInputEvent();

                Math::Vector2i prevPosition;
                Math::Vector2i currPosition;

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