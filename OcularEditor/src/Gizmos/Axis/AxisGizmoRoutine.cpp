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
              m_CurrentlyTranslating(false)
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
            auto attachedParent = m_Parent->getParent()->getParent();

            if(attachedParent)
            {
                const Math::Vector3f axisDir     = attachedParent->getTransform().getRight();
                const Math::Vector3f planeNormal = attachedParent->getTransform().getForwards();

                translateAlongAxis(axisDir, planeNormal);
            }
        }

        void AxisGizmoRoutine::updatePositionAxisY()
        {
            auto attachedParent = m_Parent->getParent()->getParent();

            if(attachedParent)
            {
                const Math::Vector3f axisDir     = attachedParent->getTransform().getUp();
                const Math::Vector3f planeNormal = attachedParent->getTransform().getRight();

                translateAlongAxis(axisDir, planeNormal);
            }
        }

        void AxisGizmoRoutine::updatePositionAxisZ()
        {
            auto attachedParent = m_Parent->getParent()->getParent();

            if(attachedParent)
            {
                const Math::Vector3f axisDir     = attachedParent->getTransform().getForwards();
                const Math::Vector3f planeNormal = attachedParent->getTransform().getUp();

                translateAlongAxis(axisDir, planeNormal);
            }
        }

        void AxisGizmoRoutine::translateAlongAxis(Math::Vector3f const& axis, Math::Vector3f const& planeNormal)
        {
            /**
             * To perform a translation along an arbitrary axis the following information is needed:
             *
             *     1. The axis to translate along
             *     2. Normal of a plane that lies on the axis (normal is perpendicular to the axis)
             *
             * Using this information, we can perform the translation using the following steps:
             *
             *     1. Create a ray projecting from the mouse position in screen-space into our world
             *     2. Create a plane whose origin is the parent position and normal is provided 
             *     3. Find the intersection point of the ray and plane (intersectionPoint)
             *     4. Find the vector from the parent position origin to the intersection point (toClick)
             *     5. Project the toClick vector onto our axis (projClick)
             *     6. (One time only) Calculate an initial offset to prevent 'jumping' on first translate action. 
             *     7. Translate the parent object along the projected vector in world-space
             */

            auto mainCamera = OcularCameras->getMainCamera();

            if(mainCamera)
            {
                auto attachedParent = m_Parent->getParent()->getParent();
                    
                const Math::Vector3f parentPos = attachedParent->getPosition(false);
                const Math::Ray      cameraRay = mainCamera->getPickRay(OcularInput->getMousePosition());
                const Math::Plane    plane     = Math::Plane(parentPos, planeNormal);

                Math::Vector3f intersectionPoint;
                float distance = 0.0f;

                if(plane.intersects(cameraRay, intersectionPoint, distance))
                {
                    const Math::Vector3f toClick   = intersectionPoint - parentPos;
                    const Math::Vector3f projClick = Math::Vector3f::Project(axis, toClick);

                    if(!m_CurrentlyTranslating)
                    {
                        m_ClickOffset = (axis * toClick.getLength());   // Without, the parent object origin is placed at click 
                        m_CurrentlyTranslating = true;
                    }
                    else
                    {
                        attachedParent->translate(projClick - m_ClickOffset, false);
                    }
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}