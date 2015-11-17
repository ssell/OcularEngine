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
#include "D3D11Texture.hpp"

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
         * \class D3D11RenderTexture
         */
        class D3D11RenderTexture : public RenderTexture, public D3D11Texture
        {
        public:

            /**
             * \param[in] descriptor TextureDescriptor for this RenderTexture
             * \param[in] device     The D3D11 device
             */
            D3D11RenderTexture(TextureDescriptor const& descriptor, ID3D11Device* device);

            /**
             * Constructor for use when creating a backbuffer RenderTexture
             *
             * \param[in] descriptor TextureDescriptor for this RenderTexture
             * \param[in] device     The D3D11 device
             * \param[in] swapchain  The SwapChain that owns the backbuffer texture
             */
            D3D11RenderTexture(TextureDescriptor const& descriptor, ID3D11Device* device, IDXGISwapChain* swapchain);
            ~D3D11RenderTexture();

            /**
             * \return The ID3D11RenderTargetView associated with this RenderTexture
             */
            ID3D11RenderTargetView* getD3DRenderTargetView();

            //------------------------------------------------------------
            // Inherited Methods
            
            /**
             * Frees all CPU and GPU related data for this RenderTexture.
             */
            virtual void unload() override;

            /**
             * Uploads all CPU related changes to the GPU (CPU to GPU upload)
             * \note The texture must have been created with CPU access of TextureAccess::WriteOnly or TextureAccess::ReadWrite.
             */
            virtual void apply() override;

            /**
             * Refreshes the CPU data with any GPU changes (GPU to CPU download)
             * \note The texture must have been created with CPU access of TextureAccess::ReadOnly or TextureAccess::ReadWrite.
             */
            virtual void refresh() override;

        protected:

            bool createD3DResources();
            bool createD3DRenderTarget();

            virtual bool createD3DTexture2D(TextureDescriptor const& descriptor) override;

            ID3D11RenderTargetView* m_D3DRenderTargetView;
            IDXGISwapChain* m_D3DSwapChain;                  ///< Optional for when creating as a backbuffer

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