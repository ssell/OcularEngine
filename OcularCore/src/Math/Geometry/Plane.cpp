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
#include "Math/Bounds/BoundsSphere.hpp"
#include "Math/Bounds/BoundsAABB.hpp"
#include "Math/Bounds/BoundsOBB.hpp"
#include "Math/Bounds/Ray.hpp"
#include "Math/Matrix3x3.hpp"

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

        Plane::Plane(Point3f const& a, Point3f const& b, Point3f const& c)
        {
            const Vector3f bToA = (b - a);
            const Vector3f cToA = (c - a);

            m_Normal = bToA.cross(cToA);
            m_Normal.normalize();

            m_Point = b;
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

        void Plane::normalize() 
        {
            float normalLength = m_Normal.getLength();
            m_Normal /= normalLength;
        }

        Plane Plane::getNormalized() const
        {
            Plane plane = (*this);
            plane.normalize();

            return plane;
        }

        //------------------------------------------------------------------------------
        // Intersection and Containment Testing
        //------------------------------------------------------------------------------

        bool Plane::intersects(Ray const& ray) const
        {
            return ray.intersects((*this));
        }

        bool Plane::intersects(Ray const& ray, Vector3f& point, float& distance) const
        {
            return ray.intersects((*this), point, distance);
        }

        bool Plane::intersects(BoundsSphere const& bounds, IntersectionType* result) const
        {
            return bounds.intersects((*this), result);
        }

        bool Plane::intersects(BoundsAABB const& bounds, IntersectionType* result) const
        {
            return bounds.intersects((*this), result);
        }

        bool Plane::intersects(BoundsOBB const& bounds, IntersectionType* result) const
        {
            return false;
        }

        Vector3f Plane::GetIntersectionPoint(Plane const& a, Plane const& b, Plane const& c)
        {
            // Source: Real-Time Rendering 3rd Ed. Page 783

            const Vector3f p1 = a.getPoint();
            const Vector3f n1 = a.getNormal();
            const Vector3f p2 = b.getPoint();
            const Vector3f n2 = b.getNormal();
            const Vector3f p3 = c.getPoint();
            const Vector3f n3 = c.getNormal();

            const Vector3f numerator = ((n2.cross(n3)) * (p1.dot(n1))) + ((n3.cross(n1)) * (p2.dot(n2))) + ((n1.cross(n2)) * (p3.dot(n3)));
            const float denominator = Matrix3x3f(n1, n2, n3).getDeterminant();

            return (numerator / denominator);
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}