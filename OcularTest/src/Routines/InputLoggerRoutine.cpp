/**
 * Copyright 2014-2015 Steven T Sell (ssell@ocularinteractive.com)
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

#include "Tests/Routines/InputLoggerRoutine.hpp"
#include "Scene/RoutineRegistrar.hpp"
#include "Events/Events/KeyboardInputEvent.hpp"

using namespace Ocular;
using namespace Ocular::Core;

OCULAR_REGISTER_ROUTINE(InputLoggerRoutine, "InputLogger")

//----------------------------------------------------------------------------------
// CONSTRUCTORS
//----------------------------------------------------------------------------------

InputLoggerRoutine::InputLoggerRoutine()
    : ARoutine()
{
    OcularEvents->registerListener(this, Priority::Medium);
}

InputLoggerRoutine::~InputLoggerRoutine()
{

}

//----------------------------------------------------------------------------------
// PUBLIC METHODS
//----------------------------------------------------------------------------------

bool InputLoggerRoutine::onEvent(std::shared_ptr<AEvent> event)
{
    if(event->isType("KeyboardInputEvent"))
    {
        Events::KeyboardInputEvent* inputEvent = dynamic_cast<Events::KeyboardInputEvent*>(event.get());

        if(inputEvent)
        {
            OcularLogger->info("The '", InputHandler::ToString(inputEvent->key), "' key was ", InputHandler::ToString(inputEvent->state));
        }
    }

    return true;
}

//----------------------------------------------------------------------------------
// PROTECTED METHODS
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
// PRIVATE METHODS
//----------------------------------------------------------------------------------