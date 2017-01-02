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

#include "Gizmos/Axis/AxisGizmo.hpp"
#include "Gizmos/Axis/AxisGizmoRoutine.hpp"
#include "Gizmos/Axis/AxisComponentGizmo.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        AxisGizmo::AxisGizmo(Core::SceneObject* parent)
            : Gizmo("OCULAR_INTERNAL_AxisGizmo", parent, "AxisGizmo"),
              m_ClearCount(0)
        {
            addRoutine(new AxisGizmoRoutine());
            
            m_AxisX = new AxisComponentGizmo(this, Axis::X);
            m_AxisY = new AxisComponentGizmo(this, Axis::Y);
            m_AxisZ = new AxisComponentGizmo(this, Axis::Z);
            
            m_AxisX->setName("OCULAR_INTERNAL_EDITOR_AxisX_Component");
            m_AxisY->setName("OCULAR_INTERNAL_EDITOR_AxisY_Component");
            m_AxisZ->setName("OCULAR_INTERNAL_EDITOR_AxisZ_Component");

            m_AxisY->rotate(90.0f, Math::Vector3f(0.0f, 0.0f, 1.0f));
            m_AxisZ->rotate(270.0f, Math::Vector3f(0.0f, 1.0f, 0.0f));

            setPersistent(true);

            m_AxisX->setPersistent(true);
            m_AxisY->setPersistent(true);
            m_AxisZ->setPersistent(true);
            
            m_AxisX->forceBoundsRebuild();
            m_AxisY->forceBoundsRebuild();
            m_AxisZ->forceBoundsRebuild();
        }

        AxisGizmo::~AxisGizmo()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void AxisGizmo::setSelected(bool const selected)
        {
            Gizmo::setSelected(selected);

            if(!selected)
            {
                m_AxisX->setSelected(false);
                m_AxisY->setSelected(false);
                m_AxisZ->setSelected(false);
            }
        }

        Math::Matrix4x4 AxisGizmo::getModelMatrix(bool const local) const
        {
            Math::Matrix4x4 result = SceneObject::getModelMatrix(local);

            if(m_Parent)
            {
                Math::Transform transform = m_Parent->getTransform();
                transform.setScale(Math::Vector3f(1.0f, 1.0f, 1.0f));

                result = transform.getModelMatrix();
            }

            return result;
        }

        void AxisGizmo::clearDepthBuffer()
        {
            // Clears the depth buffer once every three calls (one call per axis component)

            if(m_ClearCount == 0)
            {
                OcularGraphics->clearDepthBuffer();
            }

            m_ClearCount = (m_ClearCount + 1) % 3;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}