/**
 * Copyright 2014-2016 Steven T Sell (ssell@vertexfragment.com)
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
#ifndef __OCULAR_D3D11_TEXTURE__H__
#define __OCULAR_D3D11_TEXTURE__H__

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
         * \class D3D11Texture
         *
         * Collection of common objects between all D3D11 texture classes.
         */
        class D3D11Texture
        {
        public:

            D3D11Texture(ID3D11Device* device);
            virtual ~D3D11Texture();

            ID3D11Texture2D* getD3DTexture2D();
            ID3D11ShaderResourceView* getD3DShaderResource();

        protected:

            virtual bool createD3DTexture2D(TextureDescriptor const& descriptor);
            virtual bool createD3DShaderResource(TextureDescriptor const& descriptor);

            /**
             * Performs a GPU to CPU download of the texture data.
             * Texture data is retrieved from m_D3DTexture and stored in pixels.
             */
            void refresh(std::vector<Core::Color>& pixels, Graphics::TextureDescriptor const& descriptor);


            //------------------------------------------------------------

            ID3D11Device* m_D3DDevice;
            ID3D11Texture2D* m_D3DTexture;
            ID3D11ShaderResourceView* m_D3DShaderResourceView;
            DXGI_FORMAT m_D3DFormat;

        private:

            /**
             * Creates the temporary staging texture used when copying GPU texture data.
             */
            ID3D11Texture2D* createStagingTexture();

            /**
             * Copies data from the source data (mapped resource) to a destination buffer (typically uint8_t temporary buffer)
             */
            void copyData(void const* source, void* dest, uint32_t const sourceWidth, uint32_t const destWidth, uint32_t const height);

            /**
             * Copies 4-byte size pixel data (some variant of R8G8B8A8 or similar) from temporary source buffer to pixels container.
             */
            void copyToPixels4(uint8_t const* source, std::vector<Core::Color>& dest, Graphics::TextureDescriptor const& descriptor);

            /**
             * Copies 8-byte size pixel data (some variant of R16G16B16A16 or similar) from temporary source buffer to pixels container.
             */
            void copyToPixels8(uint8_t const* source, std::vector<Core::Color>& dest, Graphics::TextureDescriptor const& descriptor);

            /**
             * Copies 16-byte size pixel data (some variant of R32G32B32A32 or similar) from temporary source buffer to pixels container.
             */
            void copyToPixels16(uint8_t const* source, std::vector<Core::Color>& dest, Graphics::TextureDescriptor const& descriptor);
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