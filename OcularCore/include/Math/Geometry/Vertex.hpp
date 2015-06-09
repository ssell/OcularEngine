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
#ifndef __H__OCULAR_MATH_VERTEX__H__
#define __H__OCULAR_MATH_VERTEX__H__

#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Math
     * @{
     */
    namespace Math
    {
        /**
         * \enum Semantic
         *
         * List of possible semantics available to set for a vertex.
         *
         * With DirectX, a Semantic:Index (see Vertex) pairing is handled in
         * a straight-forward manner as one would expect. Example:
         *
         * <table>
         *     <tr>
         *         <th>Semantic</th>
         *         <th>Index</th>
         *         <th>DX Semantic</th>
         *     </tr>
         *     <tr>
         *         <td>Position</td>
         *         <td>0</td>
         *         <td>POSITION0</td>
         *     </tr>
         *     <tr>
         *         <td>TexCoord</td>
         *         <td>3</td>
         *         <td>TEXCOORD3</td>
         *     </tr>
         * </table>
         *
         * However, GLSL has no concept of Semantics and thus the 
         * binding of vertex values to the shader is handled differently.
         *
         * \todo Figure out how to do this for GL
         */
        enum class Semantic : uint8_t
        {
            Position = 0,
            Normal,
            Color,
            BlendWeight,
            TexCoord,
            Tangent,
            Binormal
        };

        struct VertexComponent
        {
            Vector4f value;
            Semantic type;
            uint32_t index;
        };

        /**
         * \class Vertex
         *
         * Base representation of a Vertex. A vertex contains a multitude of information
         * including spatial position, normal, texture coordinates, etc.
         *
         * Aside from the default components, such as position, additional data may be
         * added to the Vertex. For example, an additional color (aside from diffuse or
         * specular) be added:
         *
         *     Color green(0.0f, 1.0f, 0.0f, 1.0f);
         *     vertex.setValue(green, Semantic::Color, 2);
         *
         * The following default component mappings already exist:
         *
         *     Position:0 -> vertex.position
         *     Normal:0   -> vertex.normal
         *     Color:0    -> vertex.diffuse
         *     Color:1    -> vertex.specular
         *     TexCoord:0 -> vertex.texCoord
         */
        class Vertex
        {
        public:

            Vertex();
            ~Vertex();

            /**
             * Sets the value of the semantic:index mapping.
             *
             * \param[in] value    Value to set for the semantic:index. This value's components will
             *                     be automatically scaled to match what the graphics API expects. For
             *                     example, DirectX 11 expects blend weights to be provided as single
             *                     floats. So only the value's first component will be used and the 
             *                     rest is discarded.
             * \param[in] semantic Which semantic to associate the value with.
             * \param[in] index    Which index of the semantic to associate the value with. 
             *                     This must be on the range of [0, MAX_SEMANTIC_DEPTH - 1].
             */
            void setValue(Vector4f const& value, Semantic semantic, uint32_t index);

            /**
             * Retrieves the value for the given semantic:index mapping.
             *
             * \param[out] value
             * \param[in]  semantic
             * \param[in]  index    Must be on the range of [0, MAX_SEMANTIC_DEPTH - 1].
             */
            void getValue(Vector4f& value, Semantic semantic, uint32_t index);

            /**
             * Removes the mapping at semantic:index. 
             *
             * \param[in] semantic
             * \param[in] index
             */
            void clearValue(Semantic semantic, uint32_t index);

            Vector3f position;   ///< Spatial position of the vertex. Mapped to [Position][0]
            Vector3f normal;     ///< Normal vector of the vertex. Mapped to [Normal][0]
            Vector4f diffuse;    ///< Diffuse color of the vertex. Mapped to [Color][0]
            Vector4f specular;   ///< Specular color of the vertex. Mapped to [Color][1]
            Vector2f texCoord;   ///< Texture coordinate of the vertex. Mapped to [TexCoord][0]

        protected:

        private:

            VertexComponent* additional;
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