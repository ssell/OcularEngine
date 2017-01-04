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

#pragma once
#ifndef __H__OCULAR_EDITOR_GIZMO_AXIS__H__
#define __H__OCULAR_EDITOR_GIZMO_AXIS__H__

#include "Gizmos/Gizmo.hpp"
#include "Events/AEventListener.hpp"

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
         * \class AxisGizmo
         *
         * SceneObject that represents the local axis of the object it is attached to.
         *
         * It is used to both visualize the object axis and to provide a means to perform
         * a translation action from within the render frame.
         *
         * Composed of this parent object and three children objects (of type AxisComponentGizmo)
         * which represent each individual axis.
         */
        class AxisGizmo : public Gizmo
        {
        public:

            AxisGizmo(Core::SceneObject* parent = nullptr);
            virtual ~AxisGizmo();

            /**
             * Used to set all child components selected to FALSE. 
             * \param[in] selected If passed TRUE, the call does nothing.
             */
            virtual void setSelected(bool selected) override;

            /**
             * \return TRUE if any of the three component gizmos are currently selected.
             */
            virtual bool isSelected() const override;

            virtual Math::Matrix4x4 getModelMatrix(bool local = true) const override;

            void clearDepthBuffer();

        protected:

            Gizmo* m_AxisX;
            Gizmo* m_AxisY;
            Gizmo* m_AxisZ;

            uint32_t m_ClearCount;

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

//------------------------------------------------------------------------------------------

#endif