/**
 * Copyright 2014 Steven T Sell (ssell@ocularinteractive.com)
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

#pragma
#ifndef __H__OCULAR_GRAPHICS_MATERIAL__H__
#define __H__OCULAR_GRAPHICS_MATERIAL__H__

#include "RenderType.hpp"

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
        /**
         * \class Material
         * \brief Contains a complete Shader and all associated data such as textures, uniforms, etc.
         */
        class Material
        {
        public:

            Material();
            ~Material();

        protected:

        private:

            unsigned m_RenderQueuePosition;

            // Texture m_MainTexture;
            
            // VertexShader          m_VertexShader;
            // PreTesselationShader  m_PreTesselationShader;
            // PostTesselationShader m_PostTesselationShader;
            // GeometryShader        m_GeometryShader;
            // FragmentShader        m_FragmentShader;
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