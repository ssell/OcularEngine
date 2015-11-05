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
#ifndef __OCULAR_D3D11_DEPTH_TEXTURE__H__
#define __OCULAR_D3D11_DEPTH_TEXTURE__H__

#include "Graphics/Texture/DepthTexture.hpp"

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
         * \class D3D11DepthTexture
         */
        class D3D11DepthTexture : public DepthTexture
        {
        public:

            /**
             * \param[in] descriptor TextureDescriptor for this DepthTexture
             * \param[in] device     The D3D11 device
             */
            D3D11DepthTexture(TextureDescriptor const& descriptor, ID3D11Device* device);
            ~D3D11DepthTexture();

            /**
             * \return The ID3D11Texture2D associated with this DepthTexture
             */
            ID3D11Texture2D* getD3DTexture();

            /**
             * \return The ID3D11DepthStencilView associated with this DepthTexture
             */
            ID3D11DepthStencilView* getD3DDepthStencilView();

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
            bool createD3DTexture2D();
            bool createD3DDepthStencil();

            ID3D11Device*           m_D3DDevice;
            ID3D11Texture2D*        m_D3DTexture;
            ID3D11DepthStencilView* m_D3DDepthStencilView;
            IDXGISwapChain*         m_D3DSwapChain;          ///< Optional for when creating as a backbuffer

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