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

#include "stdafx.h"
#include "Routines/EditorCameraController.hpp"

#include "Scene/RoutineRegistrar.hpp"
#include "Scene/SceneObject.hpp"

#include "Events/Events/MouseScrollInputEvent.hpp"
#include "Events/SceneObjectFocusedEvent.hpp"

#include "Math/Bounds/Ray.hpp"
#include "Math/MathUtils.hpp"

OCULAR_REGISTER_ROUTINE(Ocular::Editor::EditorCameraController, "EditorCameraController")

namespace
{
    enum CameraMode
    {
        Default = 0,
        Drag,
        Look,
        Pan,
        Orbit
    };

    const float FocusProcessTime = 0.25f;       // Amount of time, in seconds, to process a camera focus move event
}

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        EditorCameraController::EditorCameraController()
            : ARoutine("EditorCameraController", "EditorCameraController"),
              m_Mode(CameraMode::Default),
              m_LookSensitivity(0.001f),
              m_PanSensitivity(0.001f),
              m_ZoomSensitivity(0.001f),          // Scroll events typically generate deltas of 120, so default to treat as 0.12
              m_OrbitSensitivity(0.003f),
              m_IsMovingFocus(false),
              m_FocusElapsed(0.0f),
              m_OrbitDistance(0.0f)
        {
            OcularEvents->registerListener(this, Core::Priority::Medium);
        }

        EditorCameraController::~EditorCameraController()
        {
            OcularEvents->unregisterListener(this);
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // Inherited Methods
        //----------------------------------------------------------------------------------

        void EditorCameraController::onUpdate(float const delta)
        {
            ARoutine::onUpdate(delta);

            if(m_Parent)
            {
                updateFocusMove(delta);
                updateCameraMode();
                handleMouseMovement();
            }
        }

        bool EditorCameraController::onEvent(std::shared_ptr<Core::AEvent> event)
        {
            if(event->isType<Core::MouseScrollInputEvent>())
            {
                handleEventMouseScroll(dynamic_cast<Core::MouseScrollInputEvent*>(event.get()));
            }
            else if(event->isType<SceneObjectFocusedEvent>())
            {
                handleEventObjectFocused(dynamic_cast<SceneObjectFocusedEvent*>(event.get()));
            }

            return true;
        }

        //----------------------------------------------------------------------------------
        // Controller Specific Methods
        //----------------------------------------------------------------------------------

        void EditorCameraController::setLookSensitivity(float sensitivity)
        {
            m_LookSensitivity = sensitivity;
        }

        float EditorCameraController::getLookSensitivity() const
        {
            return m_LookSensitivity;
        }

        void EditorCameraController::setPanSensitivity(float sensitivity)
        {
            m_PanSensitivity = sensitivity;
        }

        float EditorCameraController::getPanSensitivity() const
        {
            return m_PanSensitivity;
        }

        void EditorCameraController::setZoomSensitivity(float speed)
        {
            m_ZoomSensitivity = speed;
        }

        float EditorCameraController::getZoomSensitivity() const
        {
            return m_ZoomSensitivity;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void EditorCameraController::updateFocusMove(float const delta)
        {
            if(m_IsMovingFocus)
            {
                if(m_FocusElapsed > 0.0f)
                {
                    m_FocusElapsed -= delta;

                    if(m_Parent)
                    {
                        const float fractional = (FocusProcessTime - m_FocusElapsed) / FocusProcessTime;
                        const Math::Vector3f currPos = Math::Vector3f::Lerp(m_FocusStartPos, m_FocusEndPos, fractional);

                        m_Parent->getTransform().setPosition(currPos);
                    }
                }
                else
                {
                    m_FocusElapsed = 0.0f;
                    m_IsMovingFocus = false;
                }
            }
        }

        void EditorCameraController::updateCameraMode()
        {
            switch(m_Mode)
            {
            case CameraMode::Default:
            {
                if(OcularInput->isMouseButtonDown(Core::MouseButtons::Left))
                {
                    if(OcularInput->isKeyboardKeyDown(Core::KeyboardKeys::AltLeft) || 
                       OcularInput->isKeyboardKeyDown(Core::KeyboardKeys::AltRight))
                    {
                        m_Mode = CameraMode::Orbit;
                    }
                    else
                    {
                        m_Mode = CameraMode::Drag;
                        m_LastMousePos = OcularInput->getMousePosition();
                    }
                }
                else if(OcularInput->isMouseButtonDown(Core::MouseButtons::Right))
                {
                    m_Mode = CameraMode::Look;
                    m_LastMousePos = OcularInput->getMousePosition();
                }
                else if(OcularInput->isMouseButtonDown(Core::MouseButtons::Middle))
                {
                    m_Mode = CameraMode::Pan;
                    m_LastMousePos = OcularInput->getMousePosition();
                }

                break;
            }

            case CameraMode::Drag:
            {
                if(!OcularInput->isMouseButtonDown(Core::MouseButtons::Left))
                {
                    m_Mode = CameraMode::Default;
                }

                break;
            }

            case CameraMode::Look:
            {
                if(!OcularInput->isMouseButtonDown(Core::MouseButtons::Right))
                {
                    m_Mode = CameraMode::Default;
                }

                break;
            }

            case CameraMode::Pan:
            {
                if(!OcularInput->isMouseButtonDown(Core::MouseButtons::Middle))
                {
                    m_Mode = CameraMode::Default;
                }

                break;
            }

            case CameraMode::Orbit:
            {
                if(!OcularInput->isLeftMouseDown())
                {
                    m_Mode = CameraMode::Default;
                }
                else
                {
                    if(!OcularInput->isKeyboardKeyDown(Core::KeyboardKeys::AltLeft) &&
                       !OcularInput->isKeyboardKeyDown(Core::KeyboardKeys::AltRight))
                    {
                        m_Mode = CameraMode::Drag;
                    }
                }
            }

            default:
                m_Mode = CameraMode::Default;
                break;
            }
        }

        void EditorCameraController::handleEventMouseScroll(Core::MouseScrollInputEvent* event)
        {
            if(event)
            {
                if(m_Parent)
                {
                    // Use -delta so that scrolling 'forward' moves the camera forward
                    const float scrollDelta = static_cast<float>(-event->delta) * m_ZoomSensitivity;
                    const Math::Vector3f movement = Math::Vector3f(0.0f, 0.0f, scrollDelta);

                    m_Parent->translate(movement);
                    m_OrbitDistance += scrollDelta;
                }
            }
        }

        void EditorCameraController::handleEventObjectFocused(SceneObjectFocusedEvent* event)
        {
            if(event)
            {
                auto object = event->object;

                if(m_Parent && object)
                {
                    const Math::BoundsSphere bounds = object->getBoundsSphere(false);
                    const Math::Vector3f forward = m_Parent->getTransform().getForwards().getNormalized();

                    const float offset  = std::max(1.0f, bounds.getRadius() * 5.0f);
                    const Math::Ray ray = Math::Ray(bounds.getCenter(), forward);

                    m_FocusStartPos = m_Parent->getTransform().getPosition();
                    m_FocusEndPos   = ray.getPointAlong(offset);
                    m_IsMovingFocus = true;
                    m_FocusElapsed  = FocusProcessTime;
                    m_OrbitDistance = std::fabsf(bounds.getCenter().distanceTo(m_FocusEndPos));
                }
            }
        }

        void EditorCameraController::handleMouseMovement()
        {
            static const float DeltaMax = 200.0f;

            if(m_Mode != CameraMode::Default)
            {
                const Math::Vector2i currentPos = OcularInput->getMousePosition();

                m_DeltaVector.x = (static_cast<float>(currentPos.x) - static_cast<float>(m_LastMousePos.x));
                m_DeltaVector.y = (static_cast<float>(currentPos.y) - static_cast<float>(m_LastMousePos.y));

                if((m_DeltaVector.x > -DeltaMax) && (m_DeltaVector.x < DeltaMax) &&
                   (m_DeltaVector.y > -DeltaMax) && (m_DeltaVector.y < DeltaMax))
                {
                    m_IsMovingFocus = false;

                    switch(m_Mode)
                    {
                    case CameraMode::Drag:
                        handleMouseDrag();
                        break;

                    case CameraMode::Look:
                        handleMouseLook();
                        break;

                    case CameraMode::Pan:
                        handleMousePan();
                        break;

                    case CameraMode::Orbit:
                        handleMouseOrbit();
                        break;

                    default:
                        break;
                    }
                }

                m_LastMousePos = currentPos;
            }
        }

        void EditorCameraController::handleMouseDrag()
        {

        }

        void EditorCameraController::handleMouseLook()
        {
            m_LookEuler.x += -m_DeltaVector.y * m_LookSensitivity;
            m_LookEuler.y += -m_DeltaVector.x * m_LookSensitivity;

            m_Parent->setRotation(Math::Quaternion(m_LookEuler));
        }

        void EditorCameraController::handleMousePan()
        {
            m_Parent->translate(m_DeltaVector * m_PanSensitivity);
        }

        void EditorCameraController::handleMouseOrbit()
        {
            //------------------------------------------------------------
            // Calculate the point we are orbiting around
            // This is a point projected from our current position/forwards vector

            const Math::Ray preRay = Math::Ray(m_Parent->getPosition(), m_Parent->getTransform().getForwards().getNormalized());
            const Math::Vector3f orbitPoint = preRay.getPointAlong(-m_OrbitDistance);

            //------------------------------------------------------------
            // Rotate the camera

            handleMouseLook();

            //------------------------------------------------------------
            // Calculate our new position (post-rotate) in relation to the orbit point

            const Math::Ray postRay = Math::Ray(orbitPoint, m_Parent->getTransform().getForwards().getNormalized());
            m_Parent->setPosition(postRay.getPointAlong(m_OrbitDistance));
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}