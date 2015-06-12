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
#ifndef __H__OCULAR_MATH_PLANE__H__
#define __H__OCULAR_MATH_PLANE__H__

#include "Math/Vector3.hpp"
#include "Exceptions/Exception.hpp"

#include <array>

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
         * \class Plane
         *
         * An infinite 3D plane represented in point-normal form.
         */
        class Plane
        {
        public:

            /**
             * Creates a new plane from the given point and normal.
             *
             * \param[in] point  A point on the plane to intersect with.
             * \param[in] normal The direction of the plane.
             */
            Plane(Vector3f const& point, Vector3f const& normal);
            Plane();

            ~Plane();

            /**
             * \param[in] point A point on the plane to intersect with.
             */
            void setPoint(Vector3f const& point);
            
            /**
             * \param[in] normal The direction of the plane.
             */
            void setNormal(Vector3f const& normal);

            /**
             * \return Point that the plane intersects with.
             */
            Vector3f const& getPoint() const;
            
            /**
             * \return Normalized direction of the plane.
             */
            Vector3f const& getNormal() const;

            /**
             * Calculates the signed distance from the point to the plane.
             * 
             * The result is positive if the point is outside of the plane (in plane's positive half-space i.e. direction of normal). <br/>
             * The result is negative if the point is inside of the plane. <br/>
             * The result is 0 if the point is on the plane. <br/>
             *
             * \param[in] point
             * \return Signed distance to the plane.
             */
            float getSignedDistance(Vector3f const& point) const;

            /**
             * Calculates the point on the plane that is closest to the specified point.
             *
             * \param[in] point
             * \return Closest point on plane.
             */
            Vector3f getClosest(Vector3f const& point) const;

        protected:

        private:

            Vector3f m_Point;
            Vector3f m_Normal;
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