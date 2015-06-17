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
        class Ray;
        class BoundsSphere;
        class BoundsAABB;
        class BoundsOBB;

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

            /**
             * Creates a new plane from three points.
             *
             * The given points must all lie on the plane and be given in 
             * a counter-clockwise order.
             *
             * The point of the plane is set to 'b'. <br/>
             * The normal is set to (b - a) x (c - a) normalized.
             *
             * \param[in] a The first point on the plane
             * \param[in] b The second point on the plane
             * \param[in] c The third point on the plane
             */
            Plane(Point3f const& a, Point3f const& b, Point3f const& c);

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

            void normalize();

            Plane getNormalized() const;

            //------------------------------------------------------------------------------
            // Intersection and Containment Testing
            //------------------------------------------------------------------------------
            
            /**
             * Performs an intersection test on a ray and plane.
             *
             * Note that this operation is actually a line-plane intersection.
             * The line begins at ray origin and extends RAY_LINE_LENGTH.
             *
             * \param[in] )
             * \return TRUE if the ray and plane intersect.
             */
            bool intersects(Ray const& ray) const;

            /**
             * Performs an intersection test on a ray and plane.
             *
             * Note that this operation is actually a line-plane intersection.
             * The line begins at ray origin and extends RAY_LINE_LENGTH.
             *
             * \param[in]  ray
             * \param[out] point The point that the ray and AABB intersect, if they intersect.
             * \param[out] distance The distance from the ray origin to the point of intersection
             *
             * \return TRUE if the ray and plane intersect.
             */
            bool intersects(Ray const& ray, Vector3f& point, float& distance) const;

            /**
             * Performs an intersection test on a plane and sphere.
             *
             * If the result is Inside, then the sphere is located entirely within the plane's positive half space. <br/>
             * If the result is Outside, then the sphere is located entirely outside the plane's positive half space.
             *
             * The positive half space of the plane is the direction that the plane is facing, as described by it's normal.
             *
             * As an example, say we have the plane defined as:
             *
             *      Point: (0.0, 0.0, 0.0)
             *     Normal: (0.0, 1.0, 0.0)
             *
             * The plane is 'facing up' along the world origin.
             *
             * If the intersection test returns Outside, then the AABB is entirely in the +y world space. <br/>
             * If the intersection test returns Inside, then the AABB is entirely in the -y world space.
             *
             * \param[in]  bounds
             * \param[out] result Detailed intersection result.
             *
             * \return TRUE if the plane sphere AABB intersects, otherwise FALSE.
             */
            bool intersects(BoundsSphere const& bounds, IntersectionType* result = nullptr) const;

            /**
             * Performs an intersection test on a plane and AABB.
             *
             * If the result is Inside, then the AABB is located entirely within the plane's positive half space. <br/>
             * If the result is Outside, then the AABB is located entirely outside the plane's positive half space.
             *
             * The positive half space of the plane is the direction that the plane is facing, as described by it's normal.
             *
             * As an example, say we have the plane defined as:
             *
             *      Point: (0.0, 0.0, 0.0)
             *     Normal: (0.0, 1.0, 0.0)
             *
             * The plane is 'facing up' along the world origin.
             *
             * If the intersection test returns Outside, then the AABB is entirely in the +y world space. <br/>
             * If the intersection test returns Inside, then the AABB is entirely in the -y world space.
             *
             * \param[in]  bounds
             * \param[out] result Detailed intersection result.
             *
             * \return TRUE if the plane and AABB intersects, otherwise FALSE.
             */
            bool intersects(BoundsAABB const& bounds, IntersectionType* result = nullptr) const;

            /**
             * Performs an intersection test on a plane and OBB.
             *
             * If the result is Inside, then the OBB is located entirely within the plane's positive half space. <br/>
             * If the result is Outside, then the OBB is located entirely outside the plane's positive half space.
             *
             * The positive half space of the plane is the direction that the plane is facing, as described by it's normal.
             *
             * As an example, say we have the plane defined as:
             *
             *      Point: (0.0, 0.0, 0.0)
             *     Normal: (0.0, 1.0, 0.0)
             *
             * The plane is 'facing up' along the world origin.
             *
             * If the intersection test returns Outside, then the OBB is entirely in the +y world space. <br/>
             * If the intersection test returns Inside, then the OBB is entirely in the -y world space.
             *
             * \param[in]  bounds
             * \param[in]  plane
             * \param[out] result Detailed intersection result.
             *
             * \return TRUE if the plane and OBB intersects, otherwise FALSE.
             */
            bool intersects(BoundsOBB const& bounds, IntersectionType* result = nullptr) const;

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