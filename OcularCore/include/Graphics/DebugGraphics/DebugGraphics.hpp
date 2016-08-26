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
#ifndef __H__OCULAR_GRAPHICS_DEBUG__H__
#define __H__OCULAR_GRAPHICS_DEBUG__H__

#include "Math/Vector3.hpp"
#include "Math/Color.hpp"
#include "Math/Transform.hpp"

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
        class Mesh;
        class Material;

        /**
         * \struct DebugShape
         */
        struct DebugShape
        {
            Mesh* mesh;                 ///< Shape's mesh to render

            Core::Color color;          ///< Color to render the shape with

            uint64_t creationTime;      ///< Time that the shape was created
            uint64_t lifetime;          ///< Amount of time (in ms) that the shape should persist
        };

        /**
         * \class Debug
         * \brief Draws debug graphics such as lines, points, bounding volumes, axis, etc.
         */
        class Debug
        {
        public:

            Debug();
            ~Debug();

            //------------------------------------------------------------

            /**
             * Adds a line shape to be rendered.
             *
             * \param[in] start    Line starting point in world coordinates
             * \param[in] stop     Line stopping point in world coordinates
             * \param[in] color    Line color
             * \param[in] lifetime Length of time (in milliseconds) the line should be drawn. Lifetime of 0 indicates the line will persist forever.
             */
            void addLine(Math::Vector3f const& start, Math::Vector3f const& stop, Core::Color const& color, uint64_t lifetime);

            /**
             * Add a 3D circle shape to be rendered.
             *
             * \param[in] center   Center of the circle in world coordinates.
             * \param[in] radius   Radius of the circle in units.
             * \param[in] normal   Normal of the circle's surface.
             * \param[in] color    Color of the circle.
             * \param[in] segments Number of individual segments that comprise the circle. Minimum of 3.
             * \param[in] lifetime Length of time (in milliseconds) the line should be drawn. Lifetime of 0 indicates the line will persist forever.
             */
            void addCircle(Math::Vector3f const& center, float radius, Math::Vector3f const& normal, Core::Color const& color, uint32_t segments, uint64_t lifetime);

            /**
             * Renders all shapes that are alive.
             */
            void render();

        protected:

            bool fetchMaterial();
            void removeDeadShapes();

            //------------------------------------------------------------

            Material* m_Material;                      ///< Flat shader material used to render all debug shapes

            Math::Transform m_Transform;               ///< Default identity transform to render all debug shapes with

            std::vector<DebugShape> m_DebugShapes;     ///< Container of all debug shapes to draw

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