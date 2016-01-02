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
        {

        }

        BoundsOBB::BoundsOBB()
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

        Vector3f const& BoundsOBB::getExtents() const
        {
            return m_Extents;
        }

        Vector3f const& BoundsOBB::getDirectionX() const
        {
            return m_DirectionX;
        }

        Vector3f const& BoundsOBB::getDirectionY() const
        {
            return m_DirectionY;
        }

        Vector3f const& BoundsOBB::getDirectionZ() const
        {
            return m_DirectionZ;
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