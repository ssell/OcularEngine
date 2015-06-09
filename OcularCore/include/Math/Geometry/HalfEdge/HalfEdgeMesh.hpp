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
#ifndef __H__OCULAR_MATH_HALF_EDGE_MESH__H__
#define __H__OCULAR_MATH_HALF_EDGE_MESH__H__

#include "Math/Geometry/HalfEdge/HalfEdgeStructs.hpp"

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
        class HEMesh
        {
        public:

            HEMesh(Vertex const& a, Vertex const& b, Vertex const& c);
            HEMesh(Vector3f const& a, Vector3f const& b, Vector3f c);

            ~HEMesh();

            void addVertex(Vertex const& newVert, Vertex const& a, Vertex const& b);
            void addVertex(Vector3f const& newVert, Vector3f const& a, Vector3f const& b);


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