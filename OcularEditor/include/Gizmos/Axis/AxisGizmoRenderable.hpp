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
#ifndef __H__OCULAR_EDITOR_GIZMO_AXIS_RENDERABLE__H__
#define __H__OCULAR_EDITOR_GIZMO_AXIS_RENDERABLE__H__

#include "Scene/ARenderable.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    namespace Graphics
    {
        class Material;
        class Mesh;
    }

    /**
     * \addtogroup Editor
     * @{
     */
    namespace Editor
    {
        /**
         * \class AxisGizmoRenderable
         *
         * Special purpose renderable attached to an AxisComponentGizmo object.
         * Responsible for setting the axis color and ensuring it is drawn in front of all other objects.
         */
        class AxisGizmoRenderable : public Core::ARenderable
        {
        public:

            AxisGizmoRenderable();
            virtual ~AxisGizmoRenderable();

            virtual bool initialize() override;

            virtual bool preRender() override;
            virtual void render() override;
            virtual void postRender() override;

        protected:

            bool initializeMaterial();
            bool initializeMesh();

            //------------------------------------------------------------

            Graphics::Material* m_Material;
            Graphics::Mesh* m_Mesh;

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