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
#ifndef __H__OCULAR_GRAPHICS_TEXTURE__H__
#define __H__OCULAR_GRAPHICS_TEXTURE__H__

#include "Resources/Resource.hpp"
#include "TextureDescriptor.hpp"

#define OCULAR_MAX_TEXTURE_WIDTH  16384
#define OCULAR_MAX_TEXTURE_HEIGHT 16384

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
         * \class Texture
         * \brief Base class for all texture objects
         */
        class Texture : public Core::Resource
        {
        public:

            /**
             * \param[in] descriptor
             */
            Texture(TextureDescriptor const& descriptor);
            virtual ~Texture();

            //----------------------------------------
            // Inherited

            virtual void unload() = 0;

            /**
             * Applies any manually made pixel changes of the texture to the GPU.
             * Textures will not be updated (i.e. changes rendered) until this method is called.
             *
             * \note Texture CPU access must be set to TextureAccess::WriteOnly or TextureAccess::ReadWrite
             *       in order to modify a texture at runtime.
             */
            virtual void apply() = 0;

            /**
             * Refreshes the CPU texture data with any data stored on the GPU.
             * This action can overwrite pre-existing CPU data.
             *
             * \note Texture CPU access must be set to TextureAccess::ReadOnly or TextureAccess::ReadWrite
             *       in order to refresh the CPU data at runtime.
             */
            virtual void refresh() = 0;

            /**
             * Returns a copy of the texture descriptor that defines this texture resource.
             */
            TextureDescriptor getDescriptor() const;

        protected:

            TextureDescriptor m_Descriptor;

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