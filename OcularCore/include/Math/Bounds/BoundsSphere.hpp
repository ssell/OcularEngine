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
#ifndef __H__OCULAR_MATH_BOUNDS_SPHERE__H__
#define __H__OCULAR_MATH_BOUNDS_SPHERE__H__

#include "Math/Bounds/Bounds.hpp"
#include "Graphics/Mesh/Vertex.hpp"

#include "Math/Matrix4x4.hpp"
#include "Math/Vector4.hpp"

#include <list>
#include <vector>

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
        class BoundsAABB;
        class BoundsOBB;
        class Plane;

        /**
         * \class BoundsSphere
         */
        class BoundsSphere : public Bounds
        {
        public:

            BoundsSphere(std::list<Point3f> const& points, Math::Matrix4x4 const& matrix = Math::Matrix4x4());
            BoundsSphere(std::vector<Graphics::Vertex> const& vertices, Math::Matrix4x4 const& matrix = Math::Matrix4x4());
            BoundsSphere(Vector3f const& center, float radius);
            BoundsSphere();
            ~BoundsSphere();

            /**
             * Constructs the bounds from a collection of spatial points.
             * \param[in] points
             */
            void construct(std::list<Vector3f> const& points, Math::Matrix4x4 const& matrix = Math::Matrix4x4());

            /**
             *
             */
            void construct(std::vector<Graphics::Vertex> const& vertices, Math::Matrix4x4 const& matrix = Math::Matrix4x4());
            
            /**
             * Sets the center of the bounding sphere.
             * \param[in] center
             */
            void setCenter(Vector3f const& center);

            /**
             * Sets the radius of the bounding sphere.
             * \param[in] radius
             */
            void setRadius(float radius);

            /**
             * Returns the center of the bounding sphere.
             */
            Vector3f const& getCenter() const;
            
            /**
             * Returns the radius of the bounding sphere.
             */
            float getRadius() const;

            /**
             * Expands the radius of the bounding sphere by the specified amount.
             * \param[in] amount
             */
            void expand(float const amount);

            /**
             * Expands the bounding sphere so that it contains the specified point.
             * If the point is already in the sphere then no action is taken.
             *
             * \param[in] point
             */
            void expandToContain(Vector3f const& point);

            /**
             * Expands the bounding sphere so that it contains the second bounding sphere.
             * If the second sphere is already contained then no action is taken.
             *
             * \param[in] other
             */
            void expandToContain(BoundsSphere const& other);

            //------------------------------------------------------------------------------
            // Intersection and Containment Testing
            //------------------------------------------------------------------------------
            
            /**
             * Performs an intersection test on a ray and bounding sphere.
             *
             * \param[in] ray
             * \return TRUE if the ray and bounding sphere intersect.
             */
            bool intersects(Ray const& ray) const;

            /**
             * Performs an intersection test on a ray and bounding sphere.
             *
             * This version of the method also returns the point at which the two intersect.
             * If speed is of the uptmost concern and/or the exact point of intersection is
             * not required, then the other version may be used instead.
             *
             * \param[in]  ray
             * \param[out] point    The point that the ray and bounding sphere intersects.
             * \param[out] distance The distance from the ray origin to the point of intersection
             *
             * \return TRUE if the ray and bounding sphere intersect.
             */
            bool intersects(Ray const& ray, Vector3f& point, float& distance) const;

            /**
             * Performs an intersection test on two bounding spheres.
             *
             * \param[in] bounds
             * \return TRUE if the two bounding spheres intersect.
             */
            bool intersects(BoundsSphere const& bounds) const;

            /**
             * Performs an intersection test on a bounding sphere and AABB.
             *
             * \param[in] bounds
             * \return TRUE if the bounding sphere and AABB intersect.
             */
            bool intersects(BoundsAABB const& bounds) const;

            /**
             * Performs an intersection test on a bounding sphere and OBB.
             *
             * \param[in] bounds
             * \return TRUE if the bounding sphere and OBB intersect.
             */
            bool intersects(BoundsOBB const& bounds) const;

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
             * \param[in]  plane
             * \param[out] result Detailed intersection result.
             *
             * \return TRUE if the plane sphere AABB intersects, otherwise FALSE.
             */
            bool intersects(Plane const& plane, IntersectionType* result = nullptr) const;

            /**
             * Calculates if the bounds contains the specified point.
             *
             * \param[in]  point
             * \param[out] result The exact result of the containment test (intersection, outside, inside).
             *
             * \return TRUE if point is inside or intersects.
             */
            bool contains(Vector3f const& point, IntersectionType* result = nullptr) const;

            /**
             * Calculates if any portion of the specified bounding sphere is contained within the spere.
             *
             * \param[in]  sphere
             * \param[out] result The exact result of the containment test (intersection, outside, inside).
             *
             * \return TRUE if bounds is inside or intersects.
             */
            bool contains(BoundsSphere const& sphere, IntersectionType* result = nullptr) const;

        protected:

        private:

            Vector3f m_Center;
            float m_Radius;

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