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

#include "Math/Bounds/BoundsOBB.hpp"
#include "Math/Bounds/BoundsSphere.hpp"
#include "Math/Bounds/BoundsAABB.hpp"
#include "Math/Bounds/Ray.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        BoundsOBB::BoundsOBB(Vector3f const& center, Vector3f const& extents, Vector3f const& xDir, Vector3f const& yDir, Vector3f const& zDir)
            : Bounds(BoundsType::AABB)
        {

        }

        BoundsOBB::BoundsOBB()
            : Bounds(BoundsType::AABB)
        {
        
        }

        BoundsOBB::~BoundsOBB()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        Vector3f const& BoundsOBB::getCenter() const
        {
            return m_Center;
        }

        void BoundsOBB::setCenter(Vector3f const& center)
        {
            m_Center = center;
        }

        Vector3f const& BoundsOBB::getExtents() const
        {
            return m_Extents;
        }

        void BoundsOBB::setExtents(Vector3f const& extents)
        {
            m_Extents = extents;
        }

        Vector3f const& BoundsOBB::getDirectionX() const
        {
            return m_DirectionX;
        }

        void BoundsOBB::setDirectionX(Vector3f const& dirX)
        {
            m_DirectionX = dirX;
        }

        Vector3f const& BoundsOBB::getDirectionY() const
        {
            return m_DirectionY;
        }

        void BoundsOBB::setDirectionY(Vector3f const& dirY)
        {
            m_DirectionY = dirY;
        }

        Vector3f const& BoundsOBB::getDirectionZ() const
        {
            return m_DirectionZ;
        }

        void BoundsOBB::setDirectionZ(Vector3f const& dirZ)
        {
            m_DirectionZ = dirZ;
        }

        //----------------------------------------------------------------------------------
        // Intersection and Containment Testing
        //----------------------------------------------------------------------------------

        bool BoundsOBB::intersects(Ray const& ray) const
        {
            return false;
        }

        bool BoundsOBB::intersects(BoundsSphere const& bounds) const
        {
            return false;
        }

        bool BoundsOBB::intersects(BoundsAABB const& bounds) const
        {
            return false;
        }

        bool BoundsOBB::intersects(BoundsOBB const& bounds) const
        {
            return false;
        }

        bool BoundsOBB::intersects(Plane const& plane, IntersectionType* result) const
        {
            return false;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}