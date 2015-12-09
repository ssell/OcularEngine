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

#include "Scene/Routines/FreeFlyController.hpp"

#include "Scene/RoutineRegistrar.hpp"
#include "Scene/SceneObject.hpp"
#include "Events/Events/KeyboardInputEvent.hpp"

OCULAR_REGISTER_ROUTINE(Ocular::Core::FreeFlyController , "FreeFlyController")

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        FreeFlyController::FreeFlyController()
            : ARoutine()
        {
            OcularEvents->registerListener(this, Priority::Medium);
        }

        FreeFlyController::~FreeFlyController()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void FreeFlyController::onCreation()
        {
            if(m_Parent)
            {
                m_Parent->getTransform().setPosition(0.0f, 0.0f, 50.0f);
            }
        }

        void FreeFlyController::onUpdate(float const delta)
        {
            ARoutine::onUpdate(delta);

            if(m_Parent)
            {
                const Math::Vector3f currPosition = m_Parent->getTransform().getPosition();
                m_Parent->getTransform().setPosition(currPosition + (m_MovementModifier * delta));
            }
        }

        bool FreeFlyController::onEvent(std::shared_ptr<AEvent> event)
        {
            if(event->isType<Events::KeyboardInputEvent>())
            {
                Events::KeyboardInputEvent* inputEvent = dynamic_cast<Events::KeyboardInputEvent*>(event.get());

                switch(inputEvent->key)
                {
                case KeyboardKeys::W:
                case KeyboardKeys::UpArrow:
                {
                    if(inputEvent->state == KeyState::Pressed)
                    {
                        m_MovementModifier.z = -10.0f;
                    }
                    else
                    {
                        m_MovementModifier.z = 0.0f;
                    }

                    break;
                }

                case KeyboardKeys::A:
                case KeyboardKeys::LeftArrow:
                {
                    if(inputEvent->state == KeyState::Pressed)
                    {
                        m_MovementModifier.x = -10.0f;
                    }
                    else
                    {
                        m_MovementModifier.x = 0.0f;
                    }

                    break;
                }


                case KeyboardKeys::S:
                case KeyboardKeys::DownArrow:
                {
                    if(inputEvent->state == KeyState::Pressed)
                    {
                        m_MovementModifier.z = 10.0f;
                    }
                    else
                    {
                        m_MovementModifier.z = 0.0f;
                    }

                    break;
                }


                case KeyboardKeys::D:
                case KeyboardKeys::RightArrow:
                {
                    if(inputEvent->state == KeyState::Pressed)
                    {
                        m_MovementModifier.x = 10.0f;
                    }
                    else
                    {
                        m_MovementModifier.x = 0.0f;
                    }

                    break;
                }


                case KeyboardKeys::Q:
                {
                    if(inputEvent->state == KeyState::Pressed)
                    {
                        m_MovementModifier.y = 10.0f;
                    }
                    else
                    {
                        m_MovementModifier.y = 0.0f;
                    }

                    break;
                }


                case KeyboardKeys::Z:
                {
                    if(inputEvent->state == KeyState::Pressed)
                    {
                        m_MovementModifier.y = -10.0f;
                    }
                    else
                    {
                        m_MovementModifier.y = 0.0f;
                    }

                    break;
                }

                }
            }

            return true;
        }
    }
}