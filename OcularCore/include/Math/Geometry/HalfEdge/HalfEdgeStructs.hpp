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
#ifndef __H__OCULAR_MATH_HALF_EDGE_STRUCTS__H__
#define __H__OCULAR_MATH_HALF_EDGE_STRUCTS__H__

#include "Math/Geometry/Vertex.hpp"

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
         * Collection of data structures required to implement Half-Edge meshes.
         *
         * The Half-Edge mesh is a popular, convenient, and well-suited solution
         * to many geometric problems. One example use-case in Ocular is the 
         * creation of Convex Hulls.
         *
         * Implementation of Half-Edge is partly based on the following sources:
         *
         * http://www.openmesh.org/Documentation/OpenMesh-Doc-Latest/a00016.html
         * http://www.flipcode.com/archives/The_Half-Edge_Data_Structure.shtml
         */

        struct HEVertex;
        struct HEEdge;
        struct HEFace;

        /**
         * \class HEVertex
         *
         * Implementation of a vertex for the Half-Edge mesh system.
         */
        struct HEVertex
        {
            HEEdge* edge;        ///< One of the half-edges that starts at this vertex.
            Vertex* vertex;      ///< The base vertex.
        };

        /**
         * \class HEEdge
         *
         * Implementation of a half-edge for the Half-Edge mesh system.
         */
        struct HEEdge
        {
            HEVertex* from;      ///< The vertex this half-edge originates from.
            HEVertex* to;        ///< The vertex this half-edge points to.

            HEFace*   face;      ///< The face this half-edge belongs to.

            HEEdge*   next;      ///< The next half-edge in this face (counter-clockwise).
            HEEdge*   prev;      ///< The previous half-edge in this face (counter-clockwise).
            HEEdge*   opposite;  ///< The opposite half-edge (starts at 'to' and points to 'from').
        };

        /**
         * \class HEFace
         *
         * Implementation of a face for the Half-Edge mesh system.
         */
        struct HEFace
        {
            HEEdge* edge;        ///< One of the half-edges that bounds this face.
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