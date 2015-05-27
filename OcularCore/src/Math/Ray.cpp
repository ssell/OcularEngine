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

#include "Math/Ray.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Ray::Ray(Vector3f const& origin, Vector3f const& direction)
        {
            m_Origin = origin;
            m_Direction = direction.getNormalized();
        }

        Ray::Ray()
        {
        
        }

        Ray::~Ray()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void Ray::setOrigin(Vector3f const& origin)
        {
            m_Origin = origin;
        }

        void Ray::setDirection(Vector3f const& direction)
        {
            m_Direction = direction.getNormalized();
        }

        Vector3f const& Ray::getOrigin() const
        {
            return m_Origin;
        }

        Vector3f const& Ray::getDirection() const
        {
            return m_Direction;
        }

        Vector3f Ray::getPointAlong(float const distance) const
        {
            return (m_Origin + (m_Direction * distance));
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}