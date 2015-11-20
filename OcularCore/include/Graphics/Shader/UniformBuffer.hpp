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
#ifndef __H__OCULAR_GRAPHICS_UNIFORM_BUFFER_H__
#define __H__OCULAR_GRAPHICS_UNIFORM_BUFFER_H__

#include "Uniform.hpp"
#include <vector>

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
        enum class UniformBufferType
        {
            PerFrame = 0,
            PerView,
            PerObject,
            PerMaterial
        };

        /**
         * \class UniformBuffer
         * \brief Generic buffer for storing and binding of shader uniforms
         *
         * Typically, the UniformBuffer class is only to be used internally by the engine. For most 
         * cases, per-Material uniform access is sufficient (see the family of Material::setUniform
         * and Material::getUniform methods).
         *
         * There is normally four different instances of UniformBuffers in use at any time by
         * the Ocular engine. These are as follows:
         *
         *     Per-Frame (global values, lights, etc.)
         *     Per-Camera (view and projection matrices, eye position, etc.)
         *     Per-Object (world matrix, etc.)
         *     Per-Material (any user defined values)
         *
         * See the manual section on Shaders for more information.
         */
        class UniformBuffer
        {
        public:

            UniformBuffer(UniformBufferType type);
            ~UniformBuffer();

            virtual void bind();
            virtual void unbind();

            void setUniform(Uniform const& uniform);

            Uniform const* getUniform(std::string const& name) const;
            Uniform const* getUniform(uint32_t registerIndex) const;

        protected:

            uint32_t m_Type;
            bool m_IsDirty;

            std::vector<Uniform> m_Uniforms;    ///< User-friendly copy of Uniform data that is easily modifiable. Strictly CPU-only.

            float* m_UniformData;               ///< Raw, packed (16-byte) uniform data. Only modify when m_IsDirty is true and not in use by GPU.
            uint32_t m_UniformDataSize;         ///< Size of the raw uniform data 

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