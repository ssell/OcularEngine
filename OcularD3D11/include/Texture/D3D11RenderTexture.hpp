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
#ifndef __OCULAR_D3D11_RENDER_TEXTURE__H__
#define __OCULAR_D3D11_RENDER_TEXTURE__H__

#include "Graphics/Texture/RenderTexture.hpp"

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
        class D3D11RenderTexture : public RenderTexture
        {
        public:

            D3D11RenderTexture(uint32_t width, uint32_t height, TextureFilterMode filter = TextureFilterMode::Bilinear, TextureUsageMode usage = TextureUsageMode::Static);
            ~D3D11RenderTexture();

            bool create(ID3D11Device const* device);

            ID3D11Texture2D* getD3DTexture();
            ID3D11RenderTargetView* getD3DRenderTargetView();

            //------------------------------------------------------------
            // Inherited Methods

            void apply() override;
            void unload() override;


        protected:

            ID3D11Texture2D* m_D3DTexture;
            ID3D11RenderTargetView* m_D3DRenderTargetView;

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