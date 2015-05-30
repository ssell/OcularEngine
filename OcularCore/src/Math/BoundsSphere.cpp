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

#include "Math/BoundsSphere.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        BoundsSphere::BoundsSphere(Vector3f const& center, float const radius)
        {
            m_Center = center;
            m_Radius = radius;
        }

        BoundsSphere::BoundsSphere()
        {
        
        }

        BoundsSphere::~BoundsSphere()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void BoundsSphere::setCenter(Vector3f const& center)
        {
            m_Center = center;
        }

        void BoundsSphere::setRadius(float const radius)
        {
            m_Radius = radius;
        }

        Vector3f const& BoundsSphere::getCenter() const
        {
            return m_Center;
        }

        float BoundsSphere::getRadius() const
        {
            return m_Radius;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}