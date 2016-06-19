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

#include "Scene/SceneObjectRegistrar.hpp"
OCULAR_REGISTER_SCENEOBJECT(Ocular::Editor::AxisGizmo, "AxisGizmo");

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        AxisGizmo::AxisGizmo(Core::SceneObject* parent)
            : Core::SceneObject("OCULAR_INTERNAL_AxisGizmo", parent, "AxisGizmo")
        {
            addRoutine(new AxisGizmoRoutine());
            
            auto axisX = new AxisComponentGizmo(this, Axis::X);
            auto axisY = new AxisComponentGizmo(this, Axis::Y);
            auto axisZ = new AxisComponentGizmo(this, Axis::Z);

            axisY->rotate(90.0f, Math::Vector3f(0.0f, 0.0f, 1.0f));
            axisZ->rotate(270.0f, Math::Vector3f(0.0f, 1.0f, 0.0f));
        }

        AxisGizmo::~AxisGizmo()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void AxisGizmo::initializeChildren()
        {

        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}