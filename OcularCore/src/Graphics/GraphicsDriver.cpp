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

#include "Graphics/GraphicsDriver.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        GraphicsDriver::GraphicsDriver()
            : m_RenderState(nullptr)
        {
        
        }

        GraphicsDriver::~GraphicsDriver()
        {
            if(m_RenderState)
            {
                delete m_RenderState;
                m_RenderState = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        bool GraphicsDriver::initialize()
        {
            return false;
        }

        void GraphicsDriver::clearBuffers(Core::Color const& clearColor)
        {
            // Nothing to do without an active graphics API
        }

        void GraphicsDriver::clearDepthBuffer(float const value)
        {
            // Nothing to do without an active graphics API
        }

        void GraphicsDriver::clearStencilBuffer(uint32_t const value)
        {
            // Nothing to do without an active graphics API
        }

        void GraphicsDriver::swapBuffers()
        {
            // Nothing to do without an active graphics API
        }

        RenderState* GraphicsDriver::getRenderState()
        {
            return m_RenderState;
        }

        void GraphicsDriver::setRenderTexture(RenderTexture* texture)
        {
            // Nothing to do without an active graphics API
        }

        void GraphicsDriver::setDepthTexture(DepthTexture* texture)
        {
            // Nothing to do without an active graphics API
        }

        Material* GraphicsDriver::createMaterial() const
        {
            return new Material();
        }

        Viewport* GraphicsDriver::createViewport(float const x, float const y, float const width, float const height, float const minDepth, float const maxDepth) const
        {
            return new Viewport(x, y, width, height, minDepth, maxDepth);
        }

        //----------------------------------------------------------------------------------
        // Textures
        //----------------------------------------------------------------------------------

        Texture* GraphicsDriver::createTexture(TextureDescriptor const& descriptor) const
        {
            Texture* result = nullptr;

            switch(descriptor.type) 
            {
            case TextureType::Texture2D:
                result = createTexture2D(descriptor);
                break;

            case TextureType::RenderTexture2D:
                result = createRenderTexture(descriptor);
                break;

            case TextureType::DepthTexture2D:
                result = createDepthTexture(descriptor);
                break;

            default:
                OcularLogger->error("Unsupported texture type", OCULAR_INTERNAL_LOG("GraphicsDriver", "createTexture"));
                break;
            }

            return result;
        }

        Texture2D* GraphicsDriver::createTexture2D(TextureDescriptor const& descriptor) const
        {
            return new Texture2D(descriptor);
        }

        RenderTexture* GraphicsDriver::createRenderTexture(TextureDescriptor const& descriptor) const
        {
            return new RenderTexture(descriptor);
        }

        DepthTexture* GraphicsDriver::createDepthTexture(TextureDescriptor const& descriptor) const
        {
            return new DepthTexture(descriptor);
        }

        uint32_t GraphicsDriver::getMaxBoundTextures() const
        {
            return 0;
        }

        //----------------------------------------------------------------------------------
        // Shaders
        //----------------------------------------------------------------------------------

        VertexShader* GraphicsDriver::createVertexShader() const
        {
            return new VertexShader();
        }

        GeometryShader* GraphicsDriver::createGeometryShader() const
        {
            return new GeometryShader();
        }

        FragmentShader* GraphicsDriver::createFragmentShader() const
        {
            return new FragmentShader();
        }

        PreTessellationShader* GraphicsDriver::createPreTessellationShader() const
        {
            return new PreTessellationShader();
        }

        PostTessellationShader* GraphicsDriver::createPostTessellationShader() const
        {
            return new PostTessellationShader();
        }

        UniformBuffer* GraphicsDriver::createUniformBuffer(UniformBufferType const type) const
        {
            return new UniformBuffer(type);
        }

        //----------------------------------------------------------------------------------
        // Meshes
        //----------------------------------------------------------------------------------

        IndexBuffer* GraphicsDriver::createIndexBuffer() const
        {
            return new IndexBuffer;
        }

        VertexBuffer* GraphicsDriver::createVertexBuffer() const
        {
            return new VertexBuffer;
        }

        GPUBuffer* GraphicsDriver::createGPUBuffer(GPUBufferDescriptor const& descriptor) const
        {
            return new GPUBuffer(descriptor);
        }
        
        //----------------------------------------------------------------------------------
        // Debug Methods
        //----------------------------------------------------------------------------------

        void GraphicsDriver::drawDebugLine(Math::Vector3f const& start, Math::Vector3f const& stop, Core::Color const& color, uint64_t const lifetime)
        {
            m_Debug.addLine(start, stop, color, lifetime);
        }

        void GraphicsDriver::drawDebugCircle(Math::Vector3f const& center, float radius, Math::Vector3f const& normal, Core::Color const& color, uint32_t const segments, uint64_t const lifetime)
        {
            m_Debug.addCircle(center, radius, normal, color, segments, lifetime);
        }

        void GraphicsDriver::renderDebug()
        {
            m_Debug.render();
        }

        //----------------------------------------------------------------------------------
        // Temp Methods (to be moved to dedicated Renderer class in future)
        //----------------------------------------------------------------------------------
        
        bool GraphicsDriver::renderMesh(Mesh* mesh, uint32_t const submesh)
        {
            return false;
        }
        
        bool GraphicsDriver::renderBounds(Core::SceneObject* object, Math::BoundsType const type)
        {
            return false;
        }

        //----------------------------------------------------------------------------------
        // Frame Info
        //----------------------------------------------------------------------------------

        void GraphicsDriver::clearFrameStats()
        {
            m_LastFrameStats = m_CurrFrameStats;

            m_CurrFrameStats.clear();
            m_CurrFrameStats.frameNumber++;
        }

        FrameStats GraphicsDriver::getLastFrameStats() const
        {
            return m_LastFrameStats;
        }

        //----------------------------------------------------------------------------------
        // Miscellaneous
        //----------------------------------------------------------------------------------

        void GraphicsDriver::getDepthRange(float* near, float* far) const
        {
            if(near)
            {
                *near = 0.0f;
            }

            if(far)
            {
                *far = 1.0f;
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void GraphicsDriver::addDrawCall(uint32_t const numIndices)
        {
            m_CurrFrameStats.drawCalls++;

            const PrimitiveStyle primitiveStyle = m_RenderState->getRasterState().primitiveStyle;

            switch(primitiveStyle)
            {
            case PrimitiveStyle::PointList:
                m_CurrFrameStats.pointCount += numIndices;
                break;

            case PrimitiveStyle::LineList:
                m_CurrFrameStats.lineCount += (numIndices / 2);
                break;

            case PrimitiveStyle::LineStrip:
                m_CurrFrameStats.lineCount += (numIndices - 1);
                break;

            case PrimitiveStyle::TriangleList:
                m_CurrFrameStats.triangleCount += (numIndices / 3);
                break;

            case PrimitiveStyle::TriangleStrip:
                m_CurrFrameStats.triangleCount += (numIndices - 2);
                break;

            default:
                break;
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}