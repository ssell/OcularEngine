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

#include "Math/BoundingBox.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        BoundingBox::BoundingBox(Vector3f const& center, Vector3f const& extents)
        {
            m_Center = center;
            m_Extents = extents;
        }

        BoundingBox::BoundingBox()
        {
        
        }

        BoundingBox::~BoundingBox()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void BoundingBox::setCenter(Vector3f const& center)
        {
            m_Center = center;
        }

        void BoundingBox::setExtents(Vector3f const& extents)
        {
            m_Extents = extents;
        }

        Vector3f const& BoundingBox::getCenter() const
        {
            return m_Center;
        }

        Vector3f const& BoundingBox::getExtents() const
        {
            return m_Extents;
        }

        void BoundingBox::expand(Vector3f const& extents)
        {
        
        }

        void BoundingBox::expandToContain(Vector3f const& point)
        {
        
        }

        void BoundingBox::expandToContain(BoundingBox const& bounds)
        {
        
        }

        bool BoundingBox::contains(Vector3f const& point) const
        {
            return false;
        }

        bool BoundingBox::contains(BoundingBox const& bounds) const
        {
            return false;
        }

        bool BoundingBox::intersects(BoundingBox const& bounds) const
        {
            return false;
        }

        bool BoundingBox::intersects(Ray const& ray) const
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