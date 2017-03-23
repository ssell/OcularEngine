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
#ifndef __H__OCULAR_GRAPHICS_HELPERS_SCREEN_SPACE_QUAD__H__
#define __H__OCULAR_GRAPHICS_HELPERS_SCREEN_SPACE_QUAD__H__

#include <string>
#include <memory>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Graphics
     * @{
     */
    namespace Graphics
    {
        class Material;
        class VertexBuffer;
        class Texture;

        /**
         * \class ScreenSpaceQuad
         *
         * ScreenSpaceQuad is a helper class for easily rendering to a screen-filling quad. This is useful
         * for several different tasks including: deferred rendering, render texture resolution, etc.
         *
         * The ScreenSpaceQuad does not use a shared material and so may be modified independently of any other.
         */
        class ScreenSpaceQuad
        {
        public:

            ScreenSpaceQuad();
            ~ScreenSpaceQuad();

            /**
             * Builds the default mesh and material.
             */
            bool initialize();

            /**
             * Immediately renders the ScreenSpaceQuad.
             */
            void render();

            /**
             * Sets a texture to be used by the ScreenSpaceQuad.
             *
             * \note The default material makes use of only a single texture.
             *
             * \param[in] index 
             * \param[in] name
             * \param[in] texture
             */
            void setTexture(uint32_t index, std::string const& name, Texture* texture);

        protected:

            std::unique_ptr<Material>     m_Material;
            std::unique_ptr<VertexBuffer> m_VertexBuffer;

        private:

            ScreenSpaceQuad(ScreenSpaceQuad const& other) = delete;
            ScreenSpaceQuad& operator=(ScreenSpaceQuad const& other) = delete;
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