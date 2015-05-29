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

#include "Math/BoundsAABB.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        BoundsAABB::BoundsAABB(Vector3f const& center, Vector3f const& extents)
        {
            m_Center = center;
            m_Extents = extents;
        }

        BoundsAABB::BoundsAABB()
        {
        
        }

        BoundsAABB::~BoundsAABB()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void BoundsAABB::setCenter(Vector3f const& center)
        {
            m_Center = center;
        }

        void BoundsAABB::setExtents(Vector3f const& extents)
        {
            m_Extents = extents;
        }

        Vector3f const& BoundsAABB::getCenter() const
        {
            return m_Center;
        }

        Vector3f const& BoundsAABB::getExtents() const
        {
            return m_Extents;
        }

        Vector3f BoundsAABB::getMinPoint() const
        {
        
        }

        Vector3f BoundsAABB::getMaxPoint() const
        {
        
        }

        void BoundsAABB::expand(Vector3f const& extents)
        {
        
        }

        void BoundsAABB::expandToContain(Vector3f const& point)
        {
        
        }

        void BoundsAABB::expandToContain(BoundsAABB const& bounds)
        {
        
        }

        bool BoundsAABB::contains(Vector3f const& point) const
        {
            return false;
        }

        bool BoundsAABB::contains(BoundsAABB const& bounds) const
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