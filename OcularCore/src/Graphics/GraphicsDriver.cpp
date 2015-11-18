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
        {
        
        }

        GraphicsDriver::~GraphicsDriver()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        bool GraphicsDriver::initialize()
        {
            return false;
        }

        void GraphicsDriver::clearBuffers()
        {

        }

        void GraphicsDriver::swapBuffers()
        {

        }

        bool GraphicsDriver::bindMaterial(Material const* material)
        {
            return false;
        }

        bool GraphicsDriver::renderMesh(Mesh const* mesh)
        {
            return false;
        }

        Material* GraphicsDriver::createMaterial() const
        {
            return new Material();
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

        PreTesselationShader* GraphicsDriver::createPreTesselationShader() const
        {
            return new PreTesselationShader();
        }

        PostTesselationShader* GraphicsDriver::createPostTesselationShader() const
        {
            return new PostTesselationShader();
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

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}