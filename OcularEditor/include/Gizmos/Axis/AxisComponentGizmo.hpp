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

#pragma once
#ifndef __H__OCULAR_EDITOR_GIZMO_AXIS_COMPONENT__H__
#define __H__OCULAR_EDITOR_GIZMO_AXIS_COMPONENT__H__

#include "Gizmos/Gizmo.hpp"
#include "Events/AEventListener.hpp"

#include "Axis.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Editor
     * @{
     */
    namespace Editor
    {
        /**
         * \class AxisComponentGizmo
         *
         * Custom SceneObject representing a single local axis of an object.
         */
        class AxisComponentGizmo : public Gizmo, Core::AEventListener
        {
        public:

            AxisComponentGizmo(Core::SceneObject* parent, Axis axis);
            virtual ~AxisComponentGizmo();

            virtual bool onEvent(std::shared_ptr<Core::AEvent> event) override;
            virtual void setSelected(bool selected) override;

            Axis axis;

        protected:

        private:
        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

OCULAR_REGISTER_TYPE_CUSTOM(Ocular::Editor::AxisComponentGizmo,  "AxisComponentGizmo");

//------------------------------------------------------------------------------------------

#endif
