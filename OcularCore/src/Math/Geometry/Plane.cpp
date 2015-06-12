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

#include "Math/Geometry/Plane.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Plane::Plane(Vector3f const& point, Vector3f const& normal)
        {
            m_Point  = point;
            m_Normal = normal.getNormalized();
        }

        Plane::Plane()
        {
        
        }

        Plane::~Plane()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void Plane::setPoint(Vector3f const& point)
        {
            m_Point = point;
        }

        void Plane::setNormal(Vector3f const& normal)
        {
            m_Normal = normal.getNormalized();
        }

        Vector3f const& Plane::getPoint() const
        {
            return m_Point;
        }

        Vector3f const& Plane::getNormal() const
        {
            return m_Normal;
        }

        float Plane::getSignedDistance(Vector3f const& point) const
        {
            return (point - m_Point).dot(m_Normal);
        }

        Vector3f Plane::getClosest(Vector3f const& point) const
        {
            float sn = -m_Normal.dot(point - m_Point);
            float sd = m_Normal.dot(m_Normal);
            float sb = sn / sd;

            return (point + (m_Normal * sb));
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}