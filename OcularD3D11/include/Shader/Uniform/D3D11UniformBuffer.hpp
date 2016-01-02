/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
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
#ifndef __H__OCULAR_D3D11_SHADER_UNIFORM_BUFFER__H__
#define __H__OCULAR_D3D11_SHADER_UNIFORM_BUFFER__H__

#include "Graphics/Shader/Uniform/UniformBuffer.hpp"
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
         * \class D3D11UniformBuffer
         * \brief D3D11 implementation of a UniformBuffer (ie Shader Constant Buffer)
         */
        class D3D11UniformBuffer : public UniformBuffer
        {
        public:

            D3D11UniformBuffer(UniformBufferType type, ID3D11Device* device, ID3D11DeviceContext* context);
            virtual ~D3D11UniformBuffer();

            /**
             * Currently binds automatically to both Vertex and Fragment stages.
             */
            virtual void bind() override;
            virtual void unbind() override;

        protected:

            void packUniformData();
            void packDynamicUniformData();
            void packFixedUniformData();

            void buildD3DBuffer();
            void updateD3DBuffer();

            //------------------------------------------------------------

            ID3D11Device* m_D3DDevice;
            ID3D11DeviceContext* m_D3DDeviceContext;
            ID3D11Buffer* m_D3DBuffer;

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