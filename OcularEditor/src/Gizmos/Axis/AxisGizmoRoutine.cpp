/**
 * Copyright 2014-2016 Steven T Sell (ssell@vertexfragment.com)
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
#include "Gizmos/Axis/AxisGizmoRoutine.hpp"
#include "Gizmos/Axis/AxisComponentGizmo.hpp"

#include "Math/Bounds/Ray.hpp"
#include "Math/Geometry/Plane.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        AxisGizmoRoutine::AxisGizmoRoutine()
            : Core::ARoutine("AxisGizmoRoutine", "AxisGizmoRoutine"),
              m_CurrentlyTranslating(false),
              m_StartOffset(0.0f)
        {
            m_ParentCast = dynamic_cast<AxisComponentGizmo*>(m_Parent);
        }

        AxisGizmoRoutine::~AxisGizmoRoutine()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void AxisGizmoRoutine::onUpdate(float const delta)
        {
            if(m_ParentCast && m_ParentCast->isSelected())
            {
                if(OcularInput->isMouseButtonDown(Core::MouseButtons::Left))
                {
                    switch(m_ParentCast->axis)
                    {
                    case Axis::X:
                        updatePositionAxisX();
                        break;

                    case Axis::Y:
                        updatePositionAxisY();
                        break;

                    case Axis::Z:
                        updatePositionAxisZ();
                        break;

                    default:
                        break;
                    }
                }
                else
                {
                    m_ParentCast->setSelected(false);
                }
            }
            else
            {
                m_CurrentlyTranslating = false;
                m_StartOffset = 0.0f;
            }

            m_LastMousePos = OcularInput->getMousePosition();
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void AxisGizmoRoutine::setParent(Core::SceneObject* parent)
        {
            ARoutine::setParent(parent);
            m_ParentCast = dynamic_cast<AxisComponentGizmo*>(parent);
        }

        void AxisGizmoRoutine::updatePositionAxisX()
        {
            /**
             * Updates the position of the SceneObject that the gizmo is attached to based
             * on user dragging of the mouse. The same general approach is used for all 
             * three axis and is as follows:
             *
             * An axis-aligned plane is created at the object origin. The plane is aligned
             * parallel to the axis we are dragging along.
             *
             * A ray is projected from the camera based on mouse position. The collision of
             * this ray is checked against the axis-aligned plane.
             *
             * The relevant component of the ray-plane intersection point (.x for x-axis 
             * translation, etc.) is used as the new position for the attached object.
             *
             * An additional offset value is used when applying the position to keep the
             * object from 'jumping' when first selected.
             */

            auto mainCamera = OcularCameras->getMainCamera();

            if(mainCamera)
            {
                // Create the axis-aligned plane and the click ray

                const Math::Vector3f planeOrigin = m_Parent->getPosition(false);
                const Math::Vector3f planeNormal = m_Parent->getTransform().getForwards();

                const Math::Ray cameraRay = mainCamera->getPickRay(OcularInput->getMousePosition());
                const Math::Plane plane(planeOrigin, planeNormal);

                Math::Vector3f intersectionPoint;
                float distance = 0.0f;

                // If the ray intersects the plane (which it should always do as planes are infinite)
                if(plane.intersects(cameraRay, intersectionPoint, distance))
                {
                    // Lets clarify this parentage:
                    //     m_Parent = AxisComponentGizmo
                    //     m_Parent->getParent() = AxisGizmo
                    //     m_Parent->getParent()->getParent() = SceneObject the Axis is attached to and displaying for

                    auto attachedParent = m_Parent->getParent()->getParent();
                    
                    if(attachedParent)
                    {
                        // Set the position.x of the parent to match that of the ray-plane intersection

                        const Math::Vector3f parentPos = attachedParent->getPosition(false);

                        if(!m_CurrentlyTranslating)
                        {
                            m_StartOffset = intersectionPoint.x - parentPos.x;
                            m_CurrentlyTranslating = true;
                        }

                        const Math::Vector3f position = Math::Vector3f((intersectionPoint.x - m_StartOffset), parentPos.y, parentPos.z);
                        
                        attachedParent->setPosition(position);
                    }
                }
            }
        }

        void AxisGizmoRoutine::updatePositionAxisY()
        {
            // See AxisGizmoRoutine::updatePositionAxisX for details

            auto mainCamera = OcularCameras->getMainCamera();

            if(mainCamera)
            {
                const Math::Vector3f planeOrigin = m_Parent->getPosition(false);
                const Math::Vector3f planeNormal = m_Parent->getTransform().getForwards();

                const Math::Ray cameraRay = mainCamera->getPickRay(OcularInput->getMousePosition());
                const Math::Plane plane(planeOrigin, planeNormal);

                Math::Vector3f intersectionPoint;
                float distance = 0.0f;

                if(plane.intersects(cameraRay, intersectionPoint, distance))
                {
                    auto attachedParent = m_Parent->getParent()->getParent();

                    if(attachedParent)
                    {
                        const Math::Vector3f parentPos = attachedParent->getPosition(false);

                        if(!m_CurrentlyTranslating)
                        {
                            m_StartOffset = intersectionPoint.y - parentPos.y;
                            m_CurrentlyTranslating = true;
                        }

                        const Math::Vector3f position  = Math::Vector3f(parentPos.x, (intersectionPoint.y - m_StartOffset), parentPos.z);
                        
                        attachedParent->setPosition(position);
                    }
                }
            }
        }

        void AxisGizmoRoutine::updatePositionAxisZ()
        {
            // See AxisGizmoRoutine::updatePositionAxisX for details

            auto mainCamera = OcularCameras->getMainCamera();

            if(mainCamera)
            {
                const Math::Vector3f planeOrigin = m_Parent->getPosition(false);
                const Math::Vector3f planeNormal = m_Parent->getTransform().getUp();

                const Math::Ray cameraRay = mainCamera->getPickRay(OcularInput->getMousePosition());
                const Math::Plane plane(planeOrigin, planeNormal);

                Math::Vector3f intersectionPoint;
                float distance = 0.0f;

                if(plane.intersects(cameraRay, intersectionPoint, distance))
                {
                    auto attachedParent = m_Parent->getParent()->getParent();

                    if(attachedParent)
                    {
                        const Math::Vector3f parentPos = attachedParent->getPosition(false);

                        if(!m_CurrentlyTranslating)
                        {
                            m_StartOffset = intersectionPoint.z - parentPos.z;
                            m_CurrentlyTranslating = true;
                        }

                        const Math::Vector3f position  = Math::Vector3f(parentPos.x, parentPos.y, (intersectionPoint.z - m_StartOffset));
                        
                        attachedParent->setPosition(position);
                    }
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}