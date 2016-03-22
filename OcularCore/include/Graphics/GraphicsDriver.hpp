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
#ifndef __H__OCULAR_GRAPHICS_DRIVER__H__
#define __H__OCULAR_GRAPHICS_DRIVER__H__

#include "Graphics/Texture/RenderTexture.hpp"
#include "Graphics/Texture/DepthTexture.hpp"

#include "Graphics/Shader/VertexShader.hpp"
#include "Graphics/Shader/GeometryShader.hpp"
#include "Graphics/Shader/FragmentShader.hpp"
#include "Graphics/Shader/PreTessellationShader.hpp"
#include "Graphics/Shader/PostTessellationShader.hpp"

#include "Graphics/RenderState/RenderState.hpp"

#include "Graphics/Material/Material.hpp"
#include "Graphics/Mesh/Mesh.hpp"
#include "Graphics/Viewport.hpp"

#include "Scene/SceneObject.hpp"

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
         * \class GraphicsDriver
         */
        class GraphicsDriver
        {
        public:

            GraphicsDriver();
            virtual ~GraphicsDriver();

            /** 
             * Initializes the GraphicsDriver implementation.
             * \return FALSE if initialization failed (this should be a fatal event).
             */
            virtual bool initialize();

            /**
             * Clears the back buffers.
             */
            virtual void clearBuffers(Core::Color const& clearColor = Core::Color::DefaultClearGray());

            /**
             * Swaps the back and front buffers.
             */
            virtual void swapBuffers();

            /**
             * Returns the current RenderState for the GraphicsDriver.
             * No changes to the RenderState will take affect until the RenderState::bind method is called.
             *
             * \return The current RenderState. May return NULL if no underlying graphical API (D3D, GL, etc.) is in use.
             */
            virtual RenderState* getRenderState();

            /**
             * Sets the Render Texture to direct all rendering operations towards.
             * \param[in] texture
             */
            virtual void setRenderTexture(RenderTexture* texture);

            /**
             * Sets the Depth Texture to direct all depth operations towards.
             * \param[in] texture
             */
            virtual void setDepthTexture(DepthTexture* texture);

            //------------------------------------------------------------------------------
            // Creation Methods
            //------------------------------------------------------------------------------

            /**
             * Creates a new API-specific implementation of the Material class.
             * 
             * \return Returns the new instantiated material. The caller must assume
             *         ownership of the texture and handle any cleanup. May return
             *         NULL if texture creation failed.
             */
            virtual Material* createMaterial() const;

            /**
             *
             */
            virtual Viewport* createViewport(float x, float y, float width, float height, float minDepth = 0.0f, float maxDepth = 1.0f) const;

            //------------------------------------------------------------------------------
            // Textures

            /**
             * Creates a new API-specific implementation of the Texture class.
             *
             * \param[in] descriptor
             * \return Returns the new instantiated texture. The caller must assume
             *         ownership of the texture and handle any cleanup. May return
             *         NULL if texture creation failed.
             */
            virtual Texture* createTexture(TextureDescriptor const& descriptor) const;
            
            /**
             * Creates a new API-specific implementation of the Texture2D class.
             *
             * \param[in] descriptor
             * \return Returns the new instantiated texture. The caller must assume
             *         ownership of the texture and handle any cleanup. May return
             *         NULL if texture creation failed.
             */
            virtual Texture2D* createTexture2D(TextureDescriptor const& descriptor) const;
            
            /**
             * Creates a new API-specific implementation of the RenderTexture class.
             *
             * \param[in] descriptor
             *
             * \return Returns the new instantiated texture. The caller must assume
             *         ownership of the texture and handle any cleanup. May return
             *         NULL if texture creation failed.
             */
            virtual RenderTexture* createRenderTexture(TextureDescriptor const& descriptor) const;

            /**
             * Creates a new API-specific implementation of the DepthTexture class.
             *
             * \param[in] descriptor
             * \return Returns the new instantiated texture. The caller must assume
             *         ownership of the texture and handle any cleanup. May return 
             *         NULL if texture creation failed.
             */
            virtual DepthTexture* createDepthTexture(TextureDescriptor const& descriptor) const;

            /**
             * Returns the maximum number of textures that can be bound to a single shader.
             * This is primarily for use when assigning textures to materials, but can be
             * used in other locations as well.
             */
            virtual uint32_t getMaxBoundTextures() const;

            //------------------------------------------------------------------------------
            // Shaders
            
            /**
             * Creates a new API-specific implementation of the VertexShader class.
             *
             * \return Returns the new instantiated shader. The caller must assume
             *         ownership of the shader and handle any cleanup. May return 
             *         NULL if shader creation failed.
             */
            virtual VertexShader* createVertexShader() const;
            
            /**
             * Creates a new API-specific implementation of the GeometryShader class.
             *
             * \return Returns the new instantiated shader. The caller must assume
             *         ownership of the shader and handle any cleanup. May return 
             *         NULL if shader creation failed.
             */
            virtual GeometryShader* createGeometryShader() const;
            
            /**
             * Creates a new API-specific implementation of the FragmentShader class.
             *
             * \return Returns the new instantiated shader. The caller must assume
             *         ownership of the shader and handle any cleanup. May return 
             *         NULL if shader creation failed.
             */
            virtual FragmentShader* createFragmentShader() const;
            
            /**
             * Creates a new API-specific implementation of the PreTessellationShader class.
             *
             * \return Returns the new instantiated shader. The caller must assume
             *         ownership of the shader and handle any cleanup. May return 
             *         NULL if shader creation failed.
             */
            virtual PreTessellationShader* createPreTessellationShader() const;
            
            /**
             * Creates a new API-specific implementation of the PostTessellationShader class.
             *
             * \return Returns the new instantiated shader. The caller must assume
             *         ownership of the shader and handle any cleanup. May return 
             *         NULL if shader creation failed.
             */
            virtual PostTessellationShader* createPostTessellationShader() const;

            /**
             * Creates a new API-specific implementation of the UniformBuffer class.
             *
             * \return Returns the new instantiated buffer. The caller must assume
             *         ownership of the buffer and handle any cleanup. May return 
             *         NULL if buffer creation failed.
             */
            virtual UniformBuffer* createUniformBuffer(UniformBufferType type) const;

            //------------------------------------------------------------------------------
            // Meshes

            /**
             * Creates a new API-specific implementation of the IndexBuffer class.
             *
             * \return Returns the new instantiated buffer. The caller must assume
             *         ownership of the buffer and handle any cleanup. May return 
             *         NULL if buffer creation failed.
             */
            virtual IndexBuffer* createIndexBuffer() const;

            /**
             * Creates a new API-specific implementation of the VertexBuffer class.
             *
             * \return Returns the new instantiated buffer. The caller must assume
             *         ownership of the buffer and handle any cleanup. May return 
             *         NULL if buffer creation failed.
             */
            virtual VertexBuffer* createVertexBuffer() const;

            //------------------------------------------------------------------------------
            // Temp Methods (to be moved to dedicated Renderer class in future)
            //------------------------------------------------------------------------------

            /**
             * Renders the specified mesh and it's vertex and index buffers.
             *
             * \param[in] mesh Mesh to render.
             * \return TRUE if rendered successfully. 
             */
            virtual bool renderMesh(Mesh* mesh);

            /**
             * Renders the bounds of the specified SceneObject
             *
             * \param[in] object
             * \param[in] type
             */
            virtual bool renderBounds(Core::SceneObject* object, Math::BoundsType type);

        protected:

            RenderState* m_RenderState;

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