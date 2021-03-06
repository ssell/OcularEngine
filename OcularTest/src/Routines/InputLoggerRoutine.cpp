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

#include "Tests/Routines/InputLoggerRoutine.hpp"
#include "Scene/RoutineRegistrar.hpp"

#include "Events/Events/KeyboardInputEvent.hpp"
#include "Events/Events/MouseButtonInputEvent.hpp"
#include "Events/Events/MouseMoveInputEvent.hpp"
#include "Events/Events/MouseScrollInputEvent.hpp"
#include "Events/Events/ShutdownEvent.hpp"

using namespace Ocular;
using namespace Ocular::Core;

OCULAR_REGISTER_ROUTINE(InputLoggerRoutine, "InputLogger")

//----------------------------------------------------------------------------------
// CONSTRUCTORS
//----------------------------------------------------------------------------------

InputLoggerRoutine::InputLoggerRoutine()
    : ARoutine("InputLogger", "InputLogger")
{
    OcularEvents->registerListener(this, Priority::Medium);
}

InputLoggerRoutine::~InputLoggerRoutine()
{
    OcularEvents->unregisterListener(this);
}

//----------------------------------------------------------------------------------
// PUBLIC METHODS
//----------------------------------------------------------------------------------

bool InputLoggerRoutine::onEvent(std::shared_ptr<AEvent> event)
{
    if(event->isType<KeyboardInputEvent>())
    {
        KeyboardInputEvent* inputEvent = dynamic_cast<KeyboardInputEvent*>(event.get());
        
        OcularLogger->info("The '", InputHandler::ToString(inputEvent->key), "' key was ", InputHandler::ToString(inputEvent->state));

        if((inputEvent->key == KeyboardKeys::Escape) && (inputEvent->state == KeyState::Released))
        {
            OcularEvents->queueEvent(std::make_shared<ShutdownEvent>());
        }
    }
    else if(event->isType<MouseButtonInputEvent>())
    {
        MouseButtonInputEvent* inputEvent = dynamic_cast<MouseButtonInputEvent*>(event.get());
        
        OcularLogger->info("The '", InputHandler::ToString(inputEvent->button), "' button was ", InputHandler::ToString(inputEvent->state));
    }
    else if(event->isType<MouseScrollInputEvent>())
    {
        MouseScrollInputEvent* inputEvent = dynamic_cast<MouseScrollInputEvent*>(event.get());
        
        OcularLogger->info("The mouse wheel has scrolled ", static_cast<int32_t>(inputEvent->delta));
    }
    //else if(event->isType<Events::MouseMoveInputEvent>())
    //{
        //Events::MouseMoveInputEvent* inputEvent = dynamic_cast<Events::MouseMoveInputEvent*>(event.get());

        //OcularLogger->info("Mouse move to (", inputEvent->currPosition.x, ", ", inputEvent->currPosition.y, ")");
    //}

    return true;
}

//----------------------------------------------------------------------------------
// PROTECTED METHODS
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
// PRIVATE METHODS
//----------------------------------------------------------------------------------