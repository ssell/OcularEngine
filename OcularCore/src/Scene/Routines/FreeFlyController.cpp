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

#include "Scene/Routines/FreeFlyController.hpp"

#include "Scene/RoutineRegistrar.hpp"
#include "Scene/SceneObject.hpp"
#include "Events/Events/KeyboardInputEvent.hpp"

#include "Math/Matrix3x3.hpp"

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
              m_MovementSpeed(1.0f),
              m_BurstModifier(5.0f),
              m_PreventRoll(true),
              m_IsInBurst(false)
        {
            OcularEvents->registerListener(this, Priority::Medium);
        }

        FreeFlyController::~FreeFlyController()
        {
            OcularEvents->unregisterListener(this);
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // Inherited Methods
        //----------------------------------------------------------------------------------

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
            if(event->isType<KeyboardInputEvent>())
            {
                KeyboardInputEvent* inputEvent = dynamic_cast<KeyboardInputEvent*>(event.get());

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

                case KeyboardKeys::ShiftLeft:
                {
                    if(inputEvent->state == KeyState::Pressed)
                    {
                        m_IsInBurst = true;
                    }
                    else
                    {
                        m_IsInBurst = false;
                    }

                    break;
                }

                case KeyboardKeys::Space:
                {
                    if(inputEvent->state == KeyState::Released)
                    {
                        if(m_Parent)
                        {
                            m_Euler.x = 0.0f;
                            m_Euler.y = 0.0f;
                            m_Parent->resetRotation();
                        }
                    }

                    break;
                }

                default:
                    break;

                }
            }

            return true;
        }

        //----------------------------------------------------------------------------------
        // Controller Specific Methods
        //----------------------------------------------------------------------------------

        void FreeFlyController::setLookSensitivity(float sensitivity)
        {
            m_LookSensitivity = sensitivity;
        }

        float FreeFlyController::getLookSensitivity() const
        {
            return m_LookSensitivity;
        }

        void FreeFlyController::setMovementSpeed(float speed)
        {
            m_MovementSpeed = speed;
        }

        float FreeFlyController::getMovementSpeed() const
        {
            return m_MovementSpeed;
        }

        void FreeFlyController::setBurstSpeedModifier(float modifier)
        {
            m_BurstModifier = modifier;
        }

        float FreeFlyController::getBurstSpeedModifier() const
        {
            return m_BurstModifier;
        }

        void FreeFlyController::setPreventRoll(bool prevent)
        {
            m_PreventRoll = prevent;
        }

        bool FreeFlyController::getPreventRoll() const
        {
            return m_PreventRoll;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void FreeFlyController::handleMovement(float delta)
        {
            float speed = m_MovementSpeed;

            if(m_IsInBurst)
            {
                speed *= m_BurstModifier;
            }

            m_Parent->translate(m_MovementVector * speed * delta);
        }

        void FreeFlyController::handleMouseRotation()
        {
            const Math::Vector2i currentMousePos = OcularInput->getMousePosition();

            if(currentMousePos != m_LastMousePos)
            {
                const float dX = (static_cast<float>(currentMousePos.x) - static_cast<float>(m_LastMousePos.x)) * (StaticSensitivityScale * m_LookSensitivity);
                const float dY = (static_cast<float>(currentMousePos.y) - static_cast<float>(m_LastMousePos.y)) * (StaticSensitivityScale * m_LookSensitivity);

                if(m_PreventRoll)
                {
                    m_Euler.x += -dY;
                    m_Euler.y += -dX;

                    m_Parent->setRotation(Math::Quaternion(m_Euler));
                }
                else
                {
                    Math::Quaternion rotation = Math::Quaternion(Math::Vector3f(dY, -dX, 0.0f));
                    m_Parent->rotate(rotation);

                    Math::Quaternion rotX = Math::Quaternion(Math::Vector3f(dY, 0.0f, 0.0f));
                    Math::Quaternion rotY = Math::Quaternion(Math::Vector3f(0.0f, -dX, 0.0f));
                
                    m_Parent->rotate(rotY);
                    m_Parent->rotate(rotX);
                }

                m_LastMousePos = currentMousePos;
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}