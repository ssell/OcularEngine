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
#ifndef __OCULAR_D3D11_VERTEX_BUFFER__H__
#define __OCULAR_D3D11_VERTEX_BUFFER__H__

#include "Graphics/Mesh/VertexBuffer.hpp"
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
         * \class D3D11VertexBuffer
         */
        class D3D11VertexBuffer : public VertexBuffer
        {
        public:

            D3D11VertexBuffer(ID3D11Device* device, ID3D11DeviceContext* context);
            virtual ~D3D11VertexBuffer();

            virtual bool build() override;
            virtual void bind() override;
            virtual void unbind() override;

            ID3D11Buffer* getD3DVertexBuffer();

        protected:
            
            ID3D11Device* m_D3DDevice;
            ID3D11DeviceContext* m_D3DDeviceContext;
            ID3D11Buffer* m_D3DVertexBuffer;

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