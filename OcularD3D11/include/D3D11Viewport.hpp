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
#ifndef __H__OCULAR_D3D11_GRAPHICS_VIEWPORT__H__
#define __H__OCULAR_D3D11_GRAPHICS_VIEWPORT__H__

#include "Graphics/Viewport.hpp"
#include <d3d11.h>

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
         * \class D3D11Viewport
         */
        class D3D11Viewport : public Viewport
        {
        public:

            D3D11Viewport(ID3D11DeviceContext* context, float x, float y, float width, float height, float minDepth = 0.0f, float maxDepth = 1.0f);
            virtual ~D3D11Viewport();

            virtual void bind() override;

        protected:

            ID3D11DeviceContext* m_D3DDeviceContext;
            D3D11_VIEWPORT m_D3DViewport;

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