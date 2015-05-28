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
#ifndef __H__OCULAR_MATH_BOUNDING_BOX__H__
#define __H__OCULAR_MATH_BOUNDING_BOX__H__

#include "Vector3.hpp"
#include "Ray.hpp"

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
         * \class BoundingBox
         */
        class BoundingBox
        {
        public:

            BoundingBox(Vector3f const& center, Vector3f const& extents);
            BoundingBox();
            ~BoundingBox();

            void setCenter(Vector3f const& center);
            void setExtents(Vector3f const& extents);

            Vector3f const& getCenter() const;
            Vector3f const& getExtents() const;

            void expand(Vector3f const& extents);
            void expandToContain(Vector3f const& point);
            void expandToContain(BoundingBox const& bounds);

            bool contains(Vector3f const& point) const;
            bool contains(BoundingBox const& bounds) const;

            bool intersects(BoundingBox const& bounds) const;
            bool intersects(Ray const& ray) const;

        protected:

        private:

            Vector3f m_Center;
            Vector3f m_Extents;
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