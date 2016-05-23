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

#include "Math/Bounds/Ray.hpp"
#include "Math/Bounds/BoundsSphere.hpp"
#include "Math/Bounds/BoundsAABB.hpp"
#include "Math/Bounds/BoundsOBB.hpp"
#include "Math/Geometry/Plane.hpp"

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

        //------------------------------------------------------------------------------
        // Intersection and Containment Testing
        //------------------------------------------------------------------------------

        bool Ray::intersects(Ray const& other) const
        {
            return true;
        }

        bool Ray::intersects(Point3f const& point) const
        {
            const float distance = m_Origin.distanceTo(point);
            const Point3f pointOnRay = getPointAlong(distance);

            return (point == pointOnRay);
        }

        bool Ray::intersects(Ray const& other, Point3f& point, float& distance) const
        {
            return true;
        }

        bool Ray::intersects(BoundsSphere const& bounds) const
        {
            bool result = false;

            const Vector3f l = bounds.getCenter().xyz() - m_Origin;

            const float s = l.dot(m_Direction);
            const float l2 = l.dot(l);
            const float rr = (bounds.getRadius() * bounds.getRadius());

            if((s >= 0.0f) || (l2 < rr))
            {
                const float m  = l2 - (s * s);
                const float mm = m * m;

                if(mm <= rr)
                {
                    result = true;
                }
            }

            return result;
        }

        bool Ray::intersects(BoundsSphere const& bounds, Point3f& point, float& distance) const
        {
            bool result = false;

            const Vector3f l = bounds.getCenter().xyz() - m_Origin;

            const float s = l.dot(m_Direction);
            const float l2 = l.dot(l);
            const float rr = (bounds.getRadius() * bounds.getRadius());

            if((s >= 0.0f) || (l2 < rr))
            {
                const float m  = l2 - (s * s);
                const float mm = m * m;

                if(mm <= rr)
                {
                    const float q = sqrtf(rr - mm);

                    result   = true;
                    distance = (l2 > rr) ? (s - q) : (s + q);
                    point    = getPointAlong(distance);
                }
            }

            return result;
        }

        bool Ray::intersects(BoundsAABB const& bounds) const
        {
            // AABB intersection test using the slabs method.
            // Source: Real-Time Rendering, 3rd Ed. Page 743

            // Nearly identical tto the OBB method except for the following:
            //     - Calculation for e is changed
            //     - Calculation for f is changed

            static const float epsilon = 0.000000000000001f;

            bool result = true;

            float tMin = FLT_MIN;
            float tMax = FLT_MAX;
            float t0 = 0.0f;
            float t1 = 0.0f;

            const Vector3f p = bounds.getCenter() - m_Origin;
            const Vector3f d = m_Direction;
            const Vector3f h = bounds.getExtents();

            for(uint32_t i = 0; i < 3; i++)
            {
                float e = p[i];
                float f = d[i];

                if(fabs(f) > epsilon)
                {
                    t0 = (e + h[i]) / f;
                    t1 = (e - h[i]) / f;

                    if(t0 > t1)
                    {
                        float tTemp = t0;
                        t0 = t1;
                        t1 = tTemp;
                    }

                    if(t0 > tMin)
                    {
                        tMin = t0;
                    }

                    if(t1 < tMax)
                    {
                        tMax = t1;
                    }

                    if(tMin > tMax)
                    {
                        result = false;
                        break;  // No intersection
                    }

                    if(tMax < 0.0f)
                    {
                        result = false;
                        break;  // No intersection
                    }
                }
                else if(((-e - h[i]) > 0.0f) || (-e + h[i] < 0.0f))
                {
                    result = false;
                    break;  // No intersection
                }
            }

            return result;
        }

        bool Ray::intersects(BoundsAABB const& bounds, Point3f& point, float& distance) const
        {
            // AABB intersection test using the slabs method.
            // Source: Real-Time Rendering, 3rd Ed. Page 743

            // Nearly identical tto the OBB method except for the following:
            //     - Calculation for e is changed
            //     - Calculation for f is changed

            static const float epsilon = 0.000000000000001f;

            bool result = true;

            float tMin = FLT_MIN;
            float tMax = FLT_MAX;
            float t0 = 0.0f;
            float t1 = 0.0f;

            const Vector3f p = bounds.getCenter() - m_Origin;
            const Vector3f d = m_Direction;
            const Vector3f h = bounds.getExtents();

            for(uint32_t i = 0; i < 3; i++)
            {
                float e = p[i];
                float f = d[i];

                if(fabs(f) > epsilon)
                {
                    t0 = (e + h[i]) / f;
                    t1 = (e - h[i]) / f;

                    if(t0 > t1)
                    {
                        float tTemp = t0;
                        t0 = t1;
                        t1 = tTemp;
                    }

                    if(t0 > tMin)
                    {
                        tMin = t0;
                    }

                    if(t1 < tMax)
                    {
                        tMax = t1;
                    }

                    if(tMin > tMax)
                    {
                        result = false;
                        break;  // No intersection
                    }

                    if(tMax < 0.0f)
                    {
                        result = false;
                        break;  // No intersection
                    }
                }
                else if(((-e - h[i]) > 0.0f) || (-e + h[i] < 0.0f))
                {
                    result = false;
                    break;  // No intersection
                }
            }

            if(result)
            {
                distance = (tMin > 0.0f) ? tMin : tMax;
                point = getPointAlong(distance);
            }

            return result;
        }

        bool Ray::intersects(BoundsOBB const& bounds) const
        {
            // OBB intersection test using the slabs method.
            // Source: Real-Time Rendering, 3rd Ed. Page 743

            static const float epsilon = 0.000000000000001f;

            bool result = true;

            float tMin = FLT_MIN;
            float tMax = FLT_MAX;
            float t0 = 0.0f;
            float t1 = 0.0f;
            
            const Vector3f a[3] = { bounds.getDirectionX(), bounds.getDirectionY(), bounds.getDirectionZ() };
            const Vector3f p    = bounds.getCenter() - m_Origin;
            const Vector3f d    = m_Direction;
            const Vector3f h    = bounds.getExtents();

            for(uint32_t i = 0; i < 3; i++)
            {
                float e = a[i].dot(p);
                float f = a[i].dot(d);

                if(fabs(f) > epsilon)
                {
                    t0 = (e + h[i]) / f;
                    t1 = (e - h[i]) / f;

                    if(t0 > t1)
                    {
                        float tTemp = t0;
                        t0 = t1;
                        t1 = tTemp;
                    }

                    if(t0 > tMin)
                    {
                        tMin = t0;
                    }

                    if(t1 < tMax)
                    {
                        tMax = t1;
                    }

                    if(tMin > tMax)
                    {
                        result = false;
                        break;  // No intersection
                    }

                    if(tMax < 0.0f)
                    {
                        result = false;
                        break;  // No intersection
                    }
                }
                else if(((-e - h[i]) > 0.0f) || (-e + h[i] < 0.0f))
                {
                    result = false;
                    break;  // No intersection
                }
            }

            return result;
        }

        bool Ray::intersects(BoundsOBB const& bounds, Point3f& point, float& distance) const
        {
            // OBB intersection test using the slabs method.
            // Source: Real-Time Rendering, 3rd Ed. Page 743

            static const float epsilon = 0.000000000000001f;

            bool result = true;

            float tMin = FLT_MIN;
            float tMax = FLT_MAX;
            float t0 = 0.0f;
            float t1 = 0.0f;
            
            const Vector3f a[3] = { bounds.getDirectionX(), bounds.getDirectionY(), bounds.getDirectionZ() };
            const Vector3f p    = bounds.getCenter() - m_Origin;
            const Vector3f d    = m_Direction;
            const Vector3f h    = bounds.getExtents();

            for(uint32_t i = 0; i < 3; i++)
            {
                float e = a[i].dot(p);
                float f = a[i].dot(d);

                if(fabs(f) > epsilon)
                {
                    t0 = (e + h[i]) / f;
                    t1 = (e - h[i]) / f;

                    if(t0 > t1)
                    {
                        float tTemp = t0;
                        t0 = t1;
                        t1 = tTemp;
                    }

                    if(t0 > tMin)
                    {
                        tMin = t0;
                    }

                    if(t1 < tMax)
                    {
                        tMax = t1;
                    }

                    if(tMin > tMax)
                    {
                        result = false;
                        break;  // No intersection
                    }

                    if(tMax < 0.0f)
                    {
                        result = false;
                        break;  // No intersection
                    }
                }
                else if(((-e - h[i]) > 0.0f) || (-e + h[i] < 0.0f))
                {
                    result = false;
                    break;  // No intersection
                }
            }

            if(result)
            {
                distance = (tMin > 0.0f) ? tMin : tMax;
                point = getPointAlong(distance);
            }

            return result;
        }

        bool Ray::intersects(Plane const& plane) const
        {
            // Source: isect_line_plane_v3 
            // https://developer.blender.org/diffusion/B/browse/master/source/blender/blenlib/intern/math_geom.c

            bool result = false;
            
            const Vector3f line0 = m_Origin;
            const Vector3f line1 = getPointAlong(RAY_LINE_LENGTH);

            const Vector3f planePoint  = plane.getPoint();
            const Vector3f planeNormal = plane.getNormal();

            const Vector3f u = line1 - line0;
            const Vector3f h = line0 - planePoint;

            const float dot = planeNormal.dot(u);

            if(fabsf(dot) > EPSILON_FLOAT)
            {
                result = true;
            }
            
            return result;
        }

        bool Ray::intersects(Plane const& plane, Vector3f& point, float& distance) const
        {
            // Source: isect_line_plane_v3 
            // https://developer.blender.org/diffusion/B/browse/master/source/blender/blenlib/intern/math_geom.c

            bool result = false;

            const Vector3f line0 = m_Origin;
            const Vector3f line1 = getPointAlong(RAY_LINE_LENGTH);

            const Vector3f planePoint  = plane.getPoint();
            const Vector3f planeNormal = plane.getNormal();

            const Vector3f u = line1 - line0;
            const Vector3f h = line0 - planePoint;

            const float dot = planeNormal.dot(u);

            if(fabsf(dot) > EPSILON_FLOAT)
            {
                float lambda = -planeNormal.dot(h) / dot;

                point    = line0 + (u * lambda);
                distance = m_Origin.distanceTo(point);
                result   = true;
            }
            
            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}