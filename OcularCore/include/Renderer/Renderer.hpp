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
#ifndef __H__OCULAR_CORE_RENDERER__H__
#define __H__OCULAR_CORE_RENDERER__H__

#include "Math/Matrix4x4.hpp"
#include <vector>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    namespace Graphics
    {
        class UniformBuffer;
        class Material;
    }

    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        class SceneObject;

        /**
         * \class Renderer
         */
        class Renderer
        {
        public:

            Renderer();
            ~Renderer();

            virtual void render(std::vector<SceneObject*>& objects) = 0;
            virtual void render(std::vector<SceneObject*>& objects, Graphics::Material* material) = 0;

        protected:

            /**
             * Sorts the objects in the container according to their position to the active camera and their render priority value.
             */
            void sort(std::vector<SceneObject*>& objects);

            /**
             *
             */
            void bindUniforms(SceneObject* object);

            //------------------------------------------------------------

            Graphics::UniformBuffer* m_UniformBufferPerObject;

            Math::Matrix4x4 m_CurrViewMatrix;
            Math::Matrix4x4 m_CurrProjMatrix;

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
