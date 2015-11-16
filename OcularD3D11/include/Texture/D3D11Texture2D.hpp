/**
 * Copyright 2014-2015 Steven T Sell (ssell@ocularinteractive.com)
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
#ifndef __OCULAR_D3D11_TEXTURE_2D__H__
#define __OCULAR_D3D11_TEXTURE_2D__H__

#include "Graphics/Texture/Texture2D.hpp"

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
        class D3D11Texture2D : public Texture2D
        {
        public:

            D3D11Texture2D(TextureDescriptor const& descriptor, ID3D11Device* device);
            ~D3D11Texture2D();

            virtual void unload() override;
            virtual void apply() override;
            virtual void refresh() override;

        protected:

            bool createD3DTexture2D();
            bool createD3DShaderResource();

            ID3D11Device* m_D3DDevice;
            ID3D11Texture2D* m_D3DTexture;
            ID3D11ShaderResourceView* m_D3DShaderResourceView;
            DXGI_FORMAT m_D3DFormat;

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