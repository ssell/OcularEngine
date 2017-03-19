/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "stdafx.h"

#include "Routines/InputLoggerRoutine.hpp"
#include "Scene/RoutineRegistrar.hpp"
#include "Events/Events/KeyboardInputEvent.hpp"

OCULAR_REGISTER_ROUTINE(Ocular::Editor::InputLogger, "InputLogger")

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        InputLogger::InputLogger()
            : Core::ARoutine("InputLogger", "InputLogger")
        {
            OcularEvents->registerListener(this, Core::Priority::High);
        }

        InputLogger::~InputLogger()
        {
            OcularEvents->unregisterListener(this);
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool InputLogger::onEvent(std::shared_ptr<Core::AEvent> event)
        {
            if(event->isType<Core::KeyboardInputEvent>())
            {
                Core::KeyboardInputEvent* inputEvent = dynamic_cast<Core::KeyboardInputEvent*>(event.get());

                auto key = inputEvent->key;
                auto state = inputEvent->state;

                OcularLogger->info("The '", Core::InputHandler::ToString(key), "' was ", Core::InputHandler::ToString(state));
            }

            return true;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}