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
            : Core::ARoutine("AxisGizmoRoutine", "AxisGizmoRoutine")
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

                            auto position = attachedParent->getPosition(false);
                            position.x = intersectionPoint.x;
                            
                            attachedParent->setPosition(position);
                        }
                    }
                }
                else
                {
                    m_ParentCast->setSelected(false);
                }
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

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}