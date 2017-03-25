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
#ifndef __H__OCULAR_D3D11_GRAPHICS_DRIVER__H__
#define __H__OCULAR_D3D11_GRAPHICS_DRIVER__H__

#define OCULAR_D3D_11_0 100
#define OCULAR_D3D_11_1 200
#define OCULAR_D3D_11_2 300

#if OCULAR_D3D_11_VERSION > 200
#define OCULAR_D3D_USE_11_2
#elif OCULAR_D3D11_VERSION > 100
#define OCULAR_D3D_USE_11_1
#else
#define OCULAR_D3D_USE_11_0
#endif

//------------------------------------------------------------------------------------------

#include "Graphics/GraphicsDriver.hpp"
#include "Events/AEventListener.hpp"

#if defined(OCULAR_D3D_USE_11_0)
#include <d3d11.h>
#elif defined(OCULAR_D3D_USE_11_1)
#include <d3d11_1.h>
#elif defined(OCULAR_D3D_USE_11_2)
#include <d3d11_2.h>
#endif

#if defined(OCULAR_D3D_USE_11_0)
using OD3D11Device = ID3D11Device;
using OD3D11DeviceContext = ID3D11DeviceContext;
using OD3DSwapChain = IDXGISwapChain;
#elif defined(OCULAR_D3D_USE_11_1)
using OD3D11Device = ID3D11Device1;
using OD3D11DeviceContext = ID3D11DeviceContext1;
using OD3DSwapChain = IDXGISwapChain1;
#elif defined(OCULAR_D3D_USE_11_2)
using OD3D11Device = ID3D11Device2;
using OD3D11DeviceContext = ID3D11DeviceContext2;
using OD3DSwapChain = IDXGISwapChain1;
#endif

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
        class D3D11RenderTexture;
        class ScreenSpaceQuad;

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
            virtual void clearDepthBuffer(float value = 1.0f) override;
            virtual void clearStencilBuffer(uint32_t value = 0) override;
            virtual void swapBuffers(RenderTexture* renderTexture) override;

            virtual void setRenderTexture(RenderTexture* texture) override;
            virtual void setDepthTexture(DepthTexture* texture) override;
            virtual void setRenderDepthTexture(RenderTexture* renderTexture, DepthTexture* depthTexture) override;

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
            virtual GPUBuffer* createGPUBuffer(GPUBufferDescriptor const& descriptor) const override;
            
            virtual bool renderMesh(Mesh* mesh, uint32_t submesh = 0) override;
            virtual bool renderBounds(Core::SceneObject* object, Math::BoundsType type) override;
            virtual bool render(uint32_t vertCount, uint32_t vertStart) override;

            virtual void getDepthRange(float* near, float* far) const override;

            //------------------------------------------------------------
            // D3D Specific Methods

            OD3D11Device* getD3DDevice() const;
            OD3D11DeviceContext* getD3DDeviceContext() const;
            OD3DSwapChain* getD3DSwapChain() const;

            static bool ConvertTextureDescriptor(TextureDescriptor const& source, D3D11_TEXTURE2D_DESC& dest);
            static bool ConvertTextureDescriptor(D3D11_TEXTURE2D_DESC const& source, TextureDescriptor& dest);

        protected:

            virtual bool onEvent(std::shared_ptr<Core::AEvent> event) override;
            void resizeSwapChain(uint32_t width, uint32_t height);

            bool validateWindow(std::shared_ptr<Core::AWindow> window, HWND& hwnd) const;
            bool createDeviceAndSwapChain(Core::WindowWin32 const* window, HWND const hwnd);
            
#if defined(OCULAR_D3D_USE_11_0)
            DXGI_SWAP_CHAIN_DESC createSwapChainDescription(Core::WindowWin32 const* window) const;
#else
            DXGI_SWAP_CHAIN_DESC1 createSwapChainDescription(Core::WindowWin32 const* window) const;
#endif

            bool fetchDeviceAndSwapChain1(ID3D11Device* device, ID3D11DeviceContext* context, Core::WindowWin32 const* window);
            bool fetchDeviceAndSwapChain2(ID3D11Device* device, ID3D11DeviceContext* context, Core::WindowWin32 const* window);
            void fetchSwapChainBuffer();

            void calculateMultisampling();
            void resolveRenderTexture(D3D11RenderTexture* texture);

            static bool ValidateTextureDescriptor(TextureDescriptor const& descriptor);

            void printD3DDebug();

        private:

            OD3D11Device* m_D3DDevice;                                         ///< Direct3D 11.x Device
            OD3D11DeviceContext* m_D3DDeviceContext;                           ///< Direct3D 11.x Device Context
            OD3DSwapChain* m_D3DSwapChain;                                     ///< Direct3D 11.x Swap Chain
            
            std::unique_ptr<D3D11RenderTexture> m_SwapChainRenderTexture;      ///< RenderTexture holding the Swap Chain back buffer
            std::unique_ptr<ScreenSpaceQuad> m_ScreenSpaceQuad;                ///< ScreenSpaceQuad used for resolving to the Swap Chain back buffer
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