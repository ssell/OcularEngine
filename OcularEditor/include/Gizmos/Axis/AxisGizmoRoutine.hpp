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
#ifndef __H__OCULAR_EDITOR_GIZMO_AXIS_ROUTINE__H__
#define __H__OCULAR_EDITOR_GIZMO_AXIS_ROUTINE__H__

#include "Scene/ARoutine.hpp"

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
         * \class AxisGizmoRoutine
         *
         * Special purpose routine attached to an AxisGizmo object.
         *
         * This routine is responsible for scaling the gizmo based on
         * camera distance so that it maintains a relatively constant size.
         */
        class AxisGizmoRoutine : public Core::ARoutine
        {
        public:

            AxisGizmoRoutine();
            virtual ~AxisGizmoRoutine();

            virtual void onUpdate(float delta) override;

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

//------------------------------------------------------------------------------------------

#endif