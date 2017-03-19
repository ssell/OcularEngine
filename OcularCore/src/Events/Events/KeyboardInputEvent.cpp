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

#include "Events/Events/KeyboardInputEvent.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        KeyboardInputEvent::KeyboardInputEvent(KeyboardKeys const key, KeyState const state)
            : AEvent("KeyboardInputEvent", Priority::Medium), 
              key(key), 
              state(state)
        {

        }

        KeyboardInputEvent::KeyboardInputEvent()
            : AEvent("KeyboardInputEvent", Priority::Medium),
              key(KeyboardKeys::Undefined), 
              state(KeyState::Undefined)
        {

        }

        KeyboardInputEvent::~KeyboardInputEvent()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}