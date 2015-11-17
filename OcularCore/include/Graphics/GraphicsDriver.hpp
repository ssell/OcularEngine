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
#ifndef __H__OCULAR_GRAPHICS_DRIVER__H__
#define __H__OCULAR_GRAPHICS_DRIVER__H__

#include "Graphics/Texture/RenderTexture.hpp"
#include "Graphics/Texture/DepthTexture.hpp"

#include "Graphics/Shader/VertexShader.hpp"
#include "Graphics/Shader/GeometryShader.hpp"
#include "Graphics/Shader/FragmentShader.hpp"
#include "Graphics/Shader/PreTesselationShader.hpp"
#include "Graphics/Shader/PostTesselationShader.hpp"

#include "Graphics/Material/Material.hpp"

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
        class Mesh;

        /**
         * \class GraphicsDriver
         */
        class GraphicsDriver
        {
        public:

            GraphicsDriver();
            ~GraphicsDriver();

            /** 
             * Initializes the GraphicsDriver implementation.
             * \return FALSE if initialization failed (this should be a fatal event).
             */
            virtual bool initialize();

            /**
             * Clears the back buffers.
             */
            virtual void clearBuffers();

            /**
             * Swaps the back and front buffers.
             */
            virtual void swapBuffers();

            /**
             * Binds the textures, shaders, and shader values (uniforms, samplers, etc.) 
             * associated with the specified material.
             *
             * \param[in] material Material to bind. Pass NULL to unbind active material.
             * \return TRUE if bound successfully.
             */
            virtual bool bindMaterial(Material const* material);

            /**
             * Renders the specified mesh and it's vertex and index buffers.
             *
             * \param[in] mesh Mesh to render.
             * \return TRUE if rendered successfully. 
             */
            virtual bool renderMesh(Mesh const* mesh);

            //------------------------------------------------------------------------------
            // Creation Methods
            //------------------------------------------------------------------------------

            virtual Material* createMaterial();

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
            virtual Texture* createTexture(TextureDescriptor const& descriptor);
            
            /**
             * Creates a new API-specific implementation of the Texture2D class.
             *
             * \param[in] descriptor
             * \return Returns the new instantiated texture. The caller must assume
             *         ownership of the texture and handle any cleanup. May return
             *         NULL if texture creation failed.
             */
            virtual Texture2D* createTexture2D(TextureDescriptor const& descriptor);
            
            /**
             * Creates a new API-specific implementation of the RenderTexture class.
             *
             * \param[in] descriptor
             *
             * \return Returns the new instantiated texture. The caller must assume
             *         ownership of the texture and handle any cleanup. May return
             *         NULL if texture creation failed.
             */
            virtual RenderTexture* createRenderTexture(TextureDescriptor const& descriptor);

            /**
             * Creates a new API-specific implementation of the DepthTexture class.
             *
             * \param[in] descriptor
             * \return Returns the new instantiated texture. The caller must assume
             *         ownership of the texture and handle any cleanup. May return 
             *         NULL if texture creation failed.
             */
            virtual DepthTexture* createDepthTexture(TextureDescriptor const& descriptor);

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
            virtual VertexShader* createVertexShader();
            
            /**
             * Creates a new API-specific implementation of the GeometryShader class.
             *
             * \return Returns the new instantiated shader. The caller must assume
             *         ownership of the shader and handle any cleanup. May return 
             *         NULL if shader creation failed.
             */
            virtual GeometryShader* createGeometryShader();
            
            /**
             * Creates a new API-specific implementation of the FragmentShader class.
             *
             * \return Returns the new instantiated shader. The caller must assume
             *         ownership of the shader and handle any cleanup. May return 
             *         NULL if shader creation failed.
             */
            virtual FragmentShader* createFragmentShader();
            
            /**
             * Creates a new API-specific implementation of the PreTesselationShader class.
             *
             * \return Returns the new instantiated shader. The caller must assume
             *         ownership of the shader and handle any cleanup. May return 
             *         NULL if shader creation failed.
             */
            virtual PreTesselationShader* createPreTesselationShader();
            
            /**
             * Creates a new API-specific implementation of the PostTesselationShader class.
             *
             * \return Returns the new instantiated shader. The caller must assume
             *         ownership of the shader and handle any cleanup. May return 
             *         NULL if shader creation failed.
             */
            virtual PostTesselationShader* createPostTesselationShader();

        protected:

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