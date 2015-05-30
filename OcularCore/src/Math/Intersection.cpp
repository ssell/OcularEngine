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

#include "Math/Intersection.hpp"
#include "Math/MathCommon.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        bool Intersects(Ray const& rayA, Ray const& rayB, Vector3f& point)
        {
            return false;
        }
        
        bool Intersects(Ray const& ray, BoundsSphere const& bounds)
        {
            const Vector3f l = bounds.getCenter() - ray.getOrigin();

            const float s = l.dot(ray.getDirection());
            const float l2 = l.dot(l);
            const float rr = (bounds.getRadius() * bounds.getRadius());

            return (s >= 0.0f) || (l2 < rr);
        }

        bool Intersects(Ray const& ray, BoundsSphere const& bounds, Vector3f& point, float& distance)
        {
            bool result = false;

            const Vector3f l = bounds.getCenter() - ray.getOrigin();

            const float s = l.dot(ray.getDirection());
            const float l2 = l.dot(l);
            const float rr = (bounds.getRadius() * bounds.getRadius());

            if((s >= 0.0f) || (l2 < rr))
            {
                const float m  = l2 - (s * s);
                const float mm = m * m;

                if(mm <= rr)
                {
                    const float q = sqrtf(rr - mm);

                    if(l2 > rr)
                    {
                        distance = s - q;
                    }
                    else
                    {
                        distance = s + q;
                    }

                    result = true;
                    point = ray.getPointAlong(distance);
                }
            }

            return result;
        }
        
        bool Intersects(Ray const& ray, BoundsAABB const& bounds)
        {
            // AABB intersection test using the slabs method.
            // Source: Real-Time Rendering, 3rd Ed. Page 743

            // Nearly identical tto the OBB method except for the following:
            //     - Calculation for e is changed
            //     - Calculation for f is changed

            static const float epsilon = 10e-20;

            bool result = true;

            float tMin = FLT_MIN;
            float tMax = FLT_MAX;
            float t0 = 0.0f;
            float t1 = 0.0f;

            const Vector3f p = bounds.getCenter() - ray.getOrigin();
            const Vector3f d = ray.getDirection();
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
                else if(((-epsilon - h[i]) > 0.0f) || (-e + h[i] < 0.0f))
                {
                    result = false;
                    break;  // No intersection
                }
            }

            return result;
        }
        
        bool Intersects(Ray const& ray, BoundsAABB const& bounds, Vector3f& point, float& distance)
        {
            // AABB intersection test using the slabs method.
            // Source: Real-Time Rendering, 3rd Ed. Page 743

            // Nearly identical tto the OBB method except for the following:
            //     - Calculation for e is changed
            //     - Calculation for f is changed

            static const float epsilon = 10e-20;

            bool result = true;

            float tMin = FLT_MIN;
            float tMax = FLT_MAX;
            float t0 = 0.0f;
            float t1 = 0.0f;

            const Vector3f p = bounds.getCenter() - ray.getOrigin();
            const Vector3f d = ray.getDirection();
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
                else if(((-epsilon - h[i]) > 0.0f) || (-e + h[i] < 0.0f))
                {
                    result = false;
                    break;  // No intersection
                }
            }

            if(result)
            {
                distance = (tMin > 0.0f) ? tMin : tMax;
                point = ray.getPointAlong(distance);
            }

            return result;
        }
        
        bool Intersects(Ray const& ray, BoundsOBB const& bounds)
        {
            // OBB intersection test using the slabs method.
            // Source: Real-Time Rendering, 3rd Ed. Page 743

            static const float epsilon = 10e-20;

            bool result = true;

            float tMin = FLT_MIN;
            float tMax = FLT_MAX;
            float t0 = 0.0f;
            float t1 = 0.0f;
            
            const Vector3f a[3] = { bounds.getVectorU(), bounds.getVectorV(), bounds.getVectorW() };
            const Vector3f p    = bounds.getCenter() - ray.getOrigin();
            const Vector3f d    = ray.getDirection();
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
                else if(((-epsilon - h[i]) > 0.0f) || (-e + h[i] < 0.0f))
                {
                    result = false;
                    break;  // No intersection
                }
            }

            return result;
        }
        
        bool Intersects(Ray const& ray, BoundsOBB const& bounds, Vector3f& point, float& distance)
        {
            // OBB intersection test using the slabs method.
            // Source: Real-Time Rendering, 3rd Ed. Page 743

            static const float epsilon = 10e-20;

            bool result = true;

            float tMin = FLT_MIN;
            float tMax = FLT_MAX;
            float t0 = 0.0f;
            float t1 = 0.0f;
            
            const Vector3f a[3] = { bounds.getVectorU(), bounds.getVectorV(), bounds.getVectorW() };
            const Vector3f p    = bounds.getCenter() - ray.getOrigin();
            const Vector3f d    = ray.getDirection();
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
                else if(((-epsilon - h[i]) > 0.0f) || (-e + h[i] < 0.0f))
                {
                    result = false;
                    break;  // No intersection
                }
            }

            if(result)
            {
                distance = (tMin > 0.0f) ? tMin : tMax;
                point = ray.getPointAlong(distance);
            }

            return result;
        }

        bool Intersects(BoundsSphere const& boundsA, BoundsSphere const& boundsB)
        {
            // Source: Real-Time Rendering, 3rd Ed. Page 763

            const Vector3f distance = boundsA.getCenter() - boundsB.getCenter();

            const float radiiSum = boundsA.getRadius() + boundsB.getRadius();
            const float distanceSquared = distance.dot(distance);
            const float radiiSumSquared = radiiSum * radiiSum;

            return !(distanceSquared > radiiSumSquared);
        }

        bool Intersects(BoundsSphere const& boundsA, BoundsAABB const& boundsB)
        {
            // Source: Real-Time Rendering, 3rd Ed. Page 764

            const Vector3f aabbMin = boundsB.getMinPoint();
            const Vector3f aabbMax = boundsB.getMaxPoint();
            const Vector3f sphereCenter = boundsA.getCenter();
            const float    sphereRadius = boundsA.getRadius();

            const Vector3f a(Max<float>((aabbMin.x - sphereCenter.x), 0.0f),
                             Max<float>((aabbMin.y - sphereCenter.y), 0.0f),
                             Max<float>((aabbMin.z - sphereCenter.z), 0.0f));

            const Vector3f b(Max<float>((sphereCenter.x - aabbMax.x), 0.0f),
                             Max<float>((sphereCenter.y - aabbMax.y), 0.0f),
                             Max<float>((sphereCenter.z - aabbMax.z), 0.0f));

            const Vector3f c = a + b;

            float distance = c.dot(c);
                       
            return !(distance > (sphereRadius * sphereRadius));
        }

        bool Intersects(BoundsAABB const& boundsA, BoundsSphere const& boundsB)
        {
            return Intersects(boundsB, boundsA);
        }

        bool Intersects(BoundsAABB const& boundsA, BoundsAABB const& boundsB)
        {
            // Source: Real-Time Rendering, 3rd Ed. Page 765

            const Vector3f minA = boundsA.getMinPoint();
            const Vector3f minB = boundsB.getMinPoint();
            const Vector3f maxA = boundsA.getMaxPoint();
            const Vector3f maxB = boundsB.getMaxPoint();

            return !((minA.x > maxB.x) || (minB.x > maxA.x) ||
                     (minA.y > maxB.y) || (minB.y > maxA.y) ||
                     (minA.z > maxB.z) || (minB.z > maxA.z));
        }

        bool Intersects(BoundsOBB const& boundsA, BoundsOBB const& boundsB)
        {
            return false;
        }
    }
}