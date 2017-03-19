/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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
#ifndef __H__OCULAR_MATH_BOUNDS_AABB__H__
#define __H__OCULAR_MATH_BOUNDS_AABB__H__

#include "Math/Bounds/Bounds.hpp"
#include "Graphics/Mesh/Vertex.hpp"

#include "Math/Matrix4x4.hpp"
#include "Math/Vector3.hpp"

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
        class BoundsSphere;
        class BoundsOBB;
        class Plane;

        /**
         * \class BoundsAABB
         *
         * Implementation of an Axis Aligned Bounding Box.
         *
         * As per it's name, an AABB is always aligned according to the world axis and
         * thus can never rotate. Instead, when the object it contains is rotated, the
         * AABB must be recalculated.
         *
         * Intersection testing with AABBs is very fast, but can be fairly inaccurate, 
         * and thus they are typically used for first pass tests of culling and collision tests.
         *
         * To perform an intersection test see the Ocular::Math::Intersects functions.
         */
        class BoundsAABB : public Bounds
        {
        public:

            /**
             * Creates a new AABB from a list of spatial points.
             * \param[in] points
             */
            BoundsAABB(std::list<Point3f> const& points, Math::Matrix4x4 const& matrix = Math::Matrix4x4());

            /**
             * 
             */
            BoundsAABB(std::vector<Graphics::Vertex> const& vertices, Math::Matrix4x4 const& matrix = Math::Matrix4x4());

            /**
             * Creates a new AABB with the specified parameters.
             *
             * \param[in] center Center position of the AABB
             * \param[in] extents Extents along each axis from the center. So an extents of (5.0, 5.0, 5.0) would result in a 10x10x10 AABB.
             */
            BoundsAABB(Vector3f const& center, Vector3f const& extents);

            BoundsAABB();

            ~BoundsAABB();

            /**
             * Constructs the bounds from a collection of spatial points.
             *
             * \param[in] points
             */
            void construct(std::list<Point3f> const& points, Math::Matrix4x4 const& matrix = Math::Matrix4x4());

            /**
             *
             */
            void construct(std::vector<Graphics::Vertex> const& vertices, Math::Matrix4x4 const& matrix = Math::Matrix4x4());

            /**
             * Sets the center point of the bounding box.
             *
             * The minimum and maximum points will be automatically updated
             * to take into account the new center.
             *
             * \param[in] center
             */
            void setCenter(Vector3f const& center);

            /**
             * Sets the positive half-lengths of the bounding box sides.
             *
             * The minimum and maximum points will be automatically updated
             * to take into account the new extents.
             *
             * \param[in] extents
             */
            void setExtents(Vector3f const& extents);

            /**
             * \return The center point of the bounding box.
             */
            Vector3f const& getCenter() const;

            /**
             * \return The extents (side half-lenths) of the bounding box.
             */
            Vector3f const& getExtents() const;

            /**
             * \return The smallest point furthest from the center that is contained within the box.
             */
            Vector3f const& getMinPoint() const;

            /**
             * \return The largest point furthest from the center that is contained within the box.
             */
            Vector3f const& getMaxPoint() const;

            /**
             * Linearly modifies the extents according to the specified values.
             * 
             * If positie modifiers are given, then the box will expand outward.
             * If negative modifiers are given, then the box will shrink inward.
             *
             * The extents can not be negative and thus will be clamped to 0.0 if necessary.
             *
             * \param[in] modifier
             */
            void expand(Vector3f const& modifier);

            /**
             * Expands the bounding box so that it contains the specified point.
             * If the box already contains the point, then no action will be taken.
             *
             * \param[in] point
             */
            void expandToContain(Vector3f const& point);

            /**
             * Expands the bounding box so that it contains the specified bounds.
             * If the box already fully contains the bounds, then no action will be taken.
             *
             * \param[in] point
             */
            void expandToContain(BoundsAABB const& bounds);

            //------------------------------------------------------------------------------
            // Intersection and Containment Testing
            //------------------------------------------------------------------------------
            
            /**
             * Performs an intersection test on a ray and AABB.
             *
             * \param[in] ray
             * \return TRUE if the ray and AABB intersect.
             */
            bool intersects(Ray const& ray) const;
            
            /**
             * Performs an intersection test on a ray and AABB.
             *
             * This version of the method also returns the point at which the two intersect.
             * If speed is of the uptmost concern and/or the exact point of intersection is
             * not required, then the other version may be used instead.
             *
             * \param[in]  ray
             * \param[out] point    The point that the ray and AABB intersect, if they intersect.
             * \param[out] distance The distance from the ray origin to the point of intersection
             *
             * \return TRUE if the ray and AABB intersect.
             */
            bool intersects(Ray const& ray, Point3f& point, float& distance) const;
            
            /**
             * Performs an intersection test on a bounding sphere and AABB.
             *
             * \param[in] bounds
             * \return TRUE if the bounding sphere and AABB intersect.
             */
            bool intersects(BoundsSphere const& bounds) const;

            /**
             * Performs an intersection test on two AABBs.
             *
             * \param[in] bounds
             * \return TRUE if the two AABBs intersect.
             */
            bool intersects(BoundsAABB const& bounds) const;
            
            /**
             * Performs an intersection test on a AABB and OBB.
             *
             * \param[in] bounds
             * \return TRUE if the bounding sphere and OBB intersect.
             */
            bool intersects(BoundsOBB const& bounds) const;
            
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
             * \param[in]  plane
             * \param[out] result Detailed intersection result.
             *
             * \return TRUE if the plane and AABB intersects, otherwise FALSE.
             */
            bool intersects(Plane const& plane, IntersectionType* result = nullptr) const;

            /**
             * Calculates if the bounds contains the specified point.
             *
             * To test for just intersection, see the series of Ocular::Math::Intersects functions.
             *
             * \param[in]  point
             * \param[out] result The exact result of the containment test (intersection, outside, inside).
             *
             * \return TRUE if point is inside or intersects.
             */
            bool contains(Vector3f const& point, IntersectionType* result = nullptr) const;

            /**
             * Calculates if any portion of the specified bounds is contained within the AABB.
             *
             * To test for just intersection, see the series of Ocular::Math::Intersects functions.
             *
             * \param[in]  bounds
             * \param[out] result The exact result of the containment test (intersection, outside, inside).
             *
             * \return TRUE if bounds is inside or intersects.
             */
            bool contains(BoundsAABB const& bounds, IntersectionType* result = nullptr) const;

        protected:

            void calculateMinMaxPoints();

        private:

            Vector3f m_Center;      ///< Center point of the box
            Vector3f m_Extents;     ///< Positive half-lengths
            Vector3f m_MinPoint;    
            Vector3f m_MaxPoint;
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