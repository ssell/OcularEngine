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

#include "OcularEngine.hpp"

OCULAR_REGISTER_ROUTINE(Ocular::Core::FreeFlyController, "FreeFlyController")

static const float StaticSensitivityScale = 0.001f;      ///< Default scaling applied to mouse looking, as even a sensitivity of 1.0 is extremely high.

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        FreeFlyController::FreeFlyController()
            : ARoutine(),
              m_LookSensitivity(1.0f),
              m_MovementModifier(1.0f)
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

        }

        void FreeFlyController::onUpdate(float const delta)
        {
            ARoutine::onUpdate(delta);

            if(m_Parent)
            {
                handleMovement(delta);
                handleMouseRotation();
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
                        m_MovementVector.z = -1.0f;
                    }
                    else
                    {
                        m_MovementVector.z = 0.0f;
                    }
                    
                    break;
                }

                case KeyboardKeys::A:
                case KeyboardKeys::LeftArrow:
                {
                    if(inputEvent->state == KeyState::Pressed)
                    {
                        m_MovementVector.x = -1.0f;
                    }
                    else
                    {
                        m_MovementVector.x = 0.0f;
                    }
                    
                    break;
                }


                case KeyboardKeys::S:
                case KeyboardKeys::DownArrow:
                {
                    if(inputEvent->state == KeyState::Pressed)
                    {
                        m_MovementVector.z = 1.0f;
                    }
                    else
                    {
                        m_MovementVector.z = 0.0f;
                    }
                    
                    break;
                }


                case KeyboardKeys::D:
                case KeyboardKeys::RightArrow:
                {
                    if(inputEvent->state == KeyState::Pressed)
                    {
                        m_MovementVector.x = 1.0f;
                    }
                    else
                    {
                        m_MovementVector.x = 0.0f;
                    }
                    
                    break;
                }


                case KeyboardKeys::Q:
                {
                    if(inputEvent->state == KeyState::Pressed)
                    {
                        m_MovementVector.y = 1.0f;
                    }
                    else
                    {
                        m_MovementVector.y = 0.0f;
                    }
                    
                    break;
                }


                case KeyboardKeys::Z:
                {
                    if(inputEvent->state == KeyState::Pressed)
                    {
                        m_MovementVector.y = -1.0f;
                    }
                    else
                    {
                        m_MovementVector.y = 0.0f;
                    }
                    
                    break;
                }

                case KeyboardKeys::Space:
                {
                    if(m_Parent)
                    {
                        m_Parent->resetRotation();
                    }

                    break;
                }

                default:
                    break;

                }
            }

            return true;
        }

        void FreeFlyController::setLookSensitivity(float sensitivity)
        {
            m_LookSensitivity = sensitivity;
        }

        float FreeFlyController::getLookSensitivity() const
        {
            return m_LookSensitivity;
        }

        void FreeFlyController::setMovementModifier(float modifier)
        {
            m_MovementModifier = modifier;
        }

        float FreeFlyController::getMovementModifier() const
        {
            return m_MovementModifier;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void FreeFlyController::handleMovement(float delta)
        {
            m_Parent->translate(m_MovementVector * m_MovementModifier * delta);
        }

        void FreeFlyController::handleMouseRotation()
        {
            Math::Vector2i currentMousePos = OcularInput->getMousePosition();

            if(currentMousePos != m_LastMousePos)
            {
                const float dX = static_cast<float>(currentMousePos.x) - static_cast<float>(m_LastMousePos.x);
                const float dY = static_cast<float>(currentMousePos.y) - static_cast<float>(m_LastMousePos.y);
                const float dZ = 0.0f;

                const Math::Vector3f deltaVec = Math::Vector3f(dX, dY, dZ);
                const Math::Vector3f deltaNorm = deltaVec.getNormalized();
                const float deltaMag = deltaVec.getMagnitude() * (StaticSensitivityScale * m_LookSensitivity);

                m_Parent->rotate(deltaMag, Math::Vector3f(deltaNorm.y, -deltaNorm.x, 0.0f));

                m_LastMousePos = currentMousePos;
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}