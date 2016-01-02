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
#ifndef __H__OCULAR_GRAPHICS_RASTER_STATE__H__
#define __H__OCULAR_GRAPHICS_RASTER_STATE__H__

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
         * \enum FillMode
         */
        enum class FillMode
        {
            Solid = 0,                                ///< Vertices are filled
            Wireframe                                 ///< Draws only lines connecting vertices
        };

        /**
         * \enum CullMode
         */
        enum class CullMode
        {
            None = 0,                                 ///< Always draws all triangles
            Front,                                    ///< Culls away front-facing triangles
            Back                                      ///< Culls away back-facing triangles
        };

        /**
         * \enum CullDirection
         */
        enum class CullDirection
        {
            CounterClockwise = 0,                     ///< A triangle is front-facing if it's vertices are ordered counter-clockwise
            Clockwise                                 ///< A triangle is front-facing if it's vertices are ordered clockwise
        };

        /**
         * \enum PrimtiveStyle
         */
        enum class PrimitiveStyle
        {
            TriangleList = 0,                         ///< Vertex data is treated as a list of triangles
            TriangleStrip,                            ///< Vertex data is treated as a strip of triangles
            PointList,                                ///< Vertex data is treated as a list of points
            LineList,                                 ///< Vertex data is treated as a list of lines
            LineStrip                                 ///< Vertex data is treated as a string of lines
        };

        /**
         * \struct RasterState
         *
         * |     State Component      |   Default Value  |
         * | ------------------------ | ---------------- |
         * | Fill Mode                | Solid            |
         * | Cull Mode                | Back             |
         * | Cull Direction           | Counterclockwise |
         * | Primitive Style          | Triangle List    |
         * | Enable Multisampling     | True             |
         * | Enable Line Antialiasing | False            |
         *
         */
        struct RasterState
        {
            FillMode fillMode;                        ///< Determines if triangles are filled during rasterization
            CullMode cullMode;                        ///< Determines what type of triangles to cull
            CullDirection cullDirection;              ///< Determines what is considered front/back-facing triangles
            PrimitiveStyle primitiveStyle;            ///< Determines how vertex data is interpreted

            bool enableMultisampling;                 ///< Enables/disable RenderTexture antialiasing
            bool enableLineAntialiasing;              ///< Enables line primitive antialiasing
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