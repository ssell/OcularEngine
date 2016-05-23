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
#ifndef __H__OCULAR_D3D11_MATERIAL__H__
#define __H__OCULAR_D3D11_MATERIAL__H__

#include "Graphics/Material/Material.hpp"
#include <d3d11.h>
#include <vector>

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
         * \class D3D11Material
         */
        class D3D11Material : public Material
        {
        public:

            D3D11Material(ID3D11DeviceContext* context);
            virtual ~D3D11Material();

            virtual void bind() override;
            virtual void unbind() override;

            virtual bool setTexture(uint32_t index, std::string const& name, Texture* texture) override;
            virtual void removeTexture(uint32_t index) override;

        protected:

            void createSampler();

            void bindTextures();
            void unbindTextures();

            //------------------------------------------------------------

            ID3D11DeviceContext* m_D3DDeviceContext;
            ID3D11SamplerState* m_D3DSampler;

            std::vector<ID3D11ShaderResourceView*> m_ShaderResourceViews;     // Array of ShaderResourceView objects to pass to the shaders.
            std::vector<ID3D11ShaderResourceView*> m_NullShaderResourceViews; // Used when unbinding textures

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