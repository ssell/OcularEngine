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

#include "Gizmos/Axis/AxisComponentGizmo.hpp"
#include "Gizmos/Axis/AxisGizmoRenderable.hpp"
#include "Gizmos/Axis/AxisGizmoRoutine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        AxisComponentGizmo::AxisComponentGizmo(Core::SceneObject* parent, Axis const axis)
            : Gizmo("AxisComponentGizmo", parent, "AxisComponentGizmo"),
              axis(axis)
        {
            AxisGizmoRenderable* renderable = new AxisGizmoRenderable();
            setRenderable(renderable);
            renderable->initialize();

            AxisGizmoRoutine* routine = new AxisGizmoRoutine();
            addRoutine(routine);
        }

        AxisComponentGizmo::~AxisComponentGizmo()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool AxisComponentGizmo::onEvent(std::shared_ptr<Core::AEvent> event)
        {
            bool result = true;

            return result;
        }

        void AxisComponentGizmo::setSelected(bool const selected)
        {
            Gizmo::setSelected(selected);
            
            AxisGizmoRenderable* renderable = dynamic_cast<AxisGizmoRenderable*>(getRenderable());

            if(renderable)
            {
                renderable->setSelected(selected);
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}