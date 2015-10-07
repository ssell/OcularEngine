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
#include "Events/Events/MouseButtonInputEvent.hpp"
#include "Events/Events/MouseMoveInputEvent.hpp"
#include "Events/Events/MouseScrollInputEvent.hpp"

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
    else if(event->isType("MouseButtonInputEvent"))
    {
        Events::MouseButtonInputEvent* inputEvent = dynamic_cast<Events::MouseButtonInputEvent*>(event.get());

        if(inputEvent)
        {
            OcularLogger->info("The '", InputHandler::ToString(inputEvent->button), "' button was ", InputHandler::ToString(inputEvent->state));
        }
    }
    else if(event->isType("MouseMoveInputEvent"))
    {
        Events::MouseMoveInputEvent* inputEvent = dynamic_cast<Events::MouseMoveInputEvent*>(event.get());

        if(inputEvent)
        {
            const Ocular::Math::Vector2i prev = inputEvent->prevPosition;
            const Ocular::Math::Vector2i curr = inputEvent->currPosition;

            OcularLogger->info("Mouse moved to (", curr.x, ", ",curr.y, ") from (", prev.x, ", ", prev.y, ")");
        }
    }
    else if(event->isType("MouseScrollInputEvent"))
    {
        Events::MouseScrollInputEvent* inputEvent = dynamic_cast<Events::MouseScrollInputEvent*>(event.get());

        if(inputEvent)
        {
            OcularLogger->info("The mouse wheel has scrolled ", static_cast<int32_t>(inputEvent->delta));
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