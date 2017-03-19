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
#ifndef __H__OCULAR_UTILITIES_COLOR_PICKER__H__
#define __H__OCULAR_UTILITIES_COLOR_PICKER__H__

#include <cstdint>
#include <vector>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    namespace Core
    {
        class SceneObject;
        class Camera;
    }

    namespace Graphics
    {
        class Material;
    }

    /**
     * \addtogroup Utils
     * @{
     */
    namespace Utils
    {
        /**
         * \class ColorPicker
         */
        class ColorPicker
        {
        public:

            static Core::SceneObject* Pick(Core::Camera* camera, uint32_t x, uint32_t y);
                                            
        protected:

            static Graphics::Material* GetMaterial();
            static void RenderObjects(std::vector<Core::SceneObject*>& objects, Graphics::Material* material);
            static void Sort(std::vector<Core::SceneObject*>& objects);
            static uint32_t GetPickedIndex(Core::Camera* camera, uint32_t x, uint32_t y);

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
