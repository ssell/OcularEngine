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
#ifndef __H__OCULAR_D3D11_GRAPHICS_DRIVER__H__
#define __H__OCULAR_D3D11_GRAPHICS_DRIVER__H__

#include "Graphics/GraphicsDriver.hpp"
#include "Events/AEventListener.hpp"
#include <d3d11.h>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    namespace Core
    {
        class AWindow;
        class WindowWin32;
    }

    /**
     * \addtogroup Graphics
     * @{
     */
    namespace Graphics
    {
        /**
         * \class GraphicsDriver
         */
        class D3D11GraphicsDriver : public GraphicsDriver, public Core::AEventListener
        {
        public:

            D3D11GraphicsDriver();
            ~D3D11GraphicsDriver();

            //------------------------------------------------------------
            // Inherited Methods

            virtual bool initialize() override;

            virtual void clearBuffers(Core::Color const& clearColor = Core::Color::DefaultClearGray()) override;
            virtual void swapBuffers() override;

            virtual void setRenderTexture(RenderTexture* texture) override;
            virtual void setDepthTexture(DepthTexture* texture) override;

            virtual Material* createMaterial() const override;
            virtual Viewport* createViewport(float x, float y, float width, float height, float minDepth = 0.0f, float maxDepth = 1.0f) const override;

            virtual Texture* createTexture(TextureDescriptor const& descriptor) const override;
            virtual Texture2D* createTexture2D(TextureDescriptor const& descriptor) const override;
            virtual RenderTexture* createRenderTexture(TextureDescriptor const& descriptor) const override;
            virtual DepthTexture* createDepthTexture(TextureDescriptor const& descriptor) const override;
            virtual uint32_t getMaxBoundTextures() const override;

            virtual VertexShader* createVertexShader() const override;
            virtual GeometryShader* createGeometryShader() const override;
            virtual FragmentShader* createFragmentShader() const override;
            virtual PreTessellationShader* createPreTessellationShader() const override;
            virtual PostTessellationShader* createPostTessellationShader() const override;
            virtual UniformBuffer* createUniformBuffer(UniformBufferType type) const override;

            virtual IndexBuffer* createIndexBuffer() const override;
            virtual VertexBuffer* createVertexBuffer() const override;
            
            virtual bool renderMesh(Mesh* mesh) override;
            virtual bool renderBounds(Core::SceneObject* object, Math::BoundsType type) override;

            //------------------------------------------------------------
            // D3D Specific Methods

            ID3D11Device* getD3DDevice() const;
            ID3D11DeviceContext* getD3DDeviceContext() const;
            IDXGISwapChain* getD3DSwapChain() const;

            static bool ConvertTextureDescriptor(TextureDescriptor const& source, D3D11_TEXTURE2D_DESC& dest);
            static bool ConvertTextureDescriptor(D3D11_TEXTURE2D_DESC const& source, TextureDescriptor& dest);

        protected:

            virtual bool onEvent(std::shared_ptr<Core::AEvent> event) override;
            void resizeSwapChain(uint32_t width, uint32_t height);

            bool validateWindow(std::shared_ptr<Core::AWindow> window, HWND& hwnd) const;
            bool createDeviceAndSwapChain(Core::WindowWin32 const* window, HWND const hwnd);
            DXGI_SWAP_CHAIN_DESC createSwapChainDescription(Core::WindowWin32 const* window) const;

            static bool ValidateTextureDescriptor(TextureDescriptor const& descriptor);

            void printD3DDebug();

        private:

            ID3D11Device* m_D3DDevice;
            ID3D11DeviceContext* m_D3DDeviceContext;
            IDXGISwapChain* m_D3DSwapChain;
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