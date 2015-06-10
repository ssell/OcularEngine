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

#include "Math/Bounds/Intersection.hpp"
#include "gtest/gtest.h"

using namespace Ocular::Math;

//------------------------------------------------------------------------------------------

TEST(Intersections, RayRay)
{
    EXPECT_TRUE(false);
}

TEST(Intersections, RaySphere)
{
    const BoundsSphere sphere(Vector3f(0.0f, 0.0f, 0.0f), 5.0f);
    
    const Ray goodRay(Vector3f(10.0f, 0.0f, 0.0f), Vector3f(-1.0f, 0.0f, 0.0f));
    const Ray badRay(Vector3f(10.0f, 10.0f, 0.0f), Vector3f(-1.0f, 0.0f, 0.0f));

    Vector3f intersectionPoint;
    float intersectionDistance;

    EXPECT_TRUE(Intersects(goodRay, sphere, intersectionPoint, intersectionDistance));
    EXPECT_TRUE((intersectionPoint == Vector3f(5.0f, 0.0f, 0.0f)));
    EXPECT_NEAR(intersectionDistance, 5.0f, EPSILON_FLOAT);

    EXPECT_FALSE(Intersects(badRay, sphere));
}

TEST(Intersections, RayAABB)
{
    const BoundsAABB aabb(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(5.0f, 5.0f, 5.0f));

    const Ray goodRay(Vector3f(10.0f, 0.0f, 0.0f), Vector3f(-1.0f, 0.0f, 0.0f));
    const Ray badRay(Vector3f(100.0f, 100.0f, 0.0f), Vector3f(-1.0f, 0.0f, 0.0f));

    Vector3f intersectionPoint;
    float intersectionDistance;

    EXPECT_TRUE(Intersects(goodRay, aabb, intersectionPoint, intersectionDistance));
    EXPECT_TRUE((intersectionPoint == Vector3f(5.0f, 0.0f, 0.0f)));
    EXPECT_NEAR(intersectionDistance, 5.0f, EPSILON_FLOAT);

    EXPECT_FALSE(Intersects(badRay, aabb));
}

TEST(Intersections, RayOBB)
{
    EXPECT_TRUE(false);
}

TEST(Intersections, RayPlane)
{
    EXPECT_TRUE(false);
}

TEST(Intersections, SphereSphere)
{
    const BoundsSphere a(Vector3f(0.0f, 0.0f, 0.0f), 10.0f);
    const BoundsSphere b(Vector3f(5.0f, 0.0f, 0.0f), 1.0f);
    const BoundsSphere c(Vector3f(20.0f, 20.0f, 20.0f), 1.0f);
    const BoundsSphere d(Vector3f(15.0f, 0.0f, 0.0f), 10.0f);
    
    EXPECT_TRUE(Intersects(a, b));
    EXPECT_TRUE(Intersects(a, d));
    EXPECT_FALSE(Intersects(a, c));
    EXPECT_FALSE(Intersects(b, c));
}

TEST(Intersections, SphereAABB)
{
    const BoundsSphere sphere(Vector3f(0.0f, 0.0f, 0.0f), 10.0f);
    const BoundsAABB aabbA(Vector3f(12.0f, 0.0f, 0.0f), Vector3f(5.0f, 5.0f, 5.0f));
    const BoundsAABB aabbB(Vector3f(30.0f, 0.0f, 0.0f), Vector3f(10.0f, 10.0f, 10.0f));

    EXPECT_TRUE(Intersects(sphere, aabbA));
    EXPECT_FALSE(Intersects(sphere, aabbB));
}

TEST(Intersections, SphereOBB)
{
    EXPECT_TRUE(false);
}

TEST(Intersections, AABBAABB)
{
    const BoundsAABB a(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(10.0f, 10.0f, 10.0f));
    const BoundsAABB b(Vector3f(20.0f, 0.0f, 0.0f), Vector3f(15.0f, 5.0f, 5.0f));
    const BoundsAABB c(Vector3f(20.0f, 10.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));

    EXPECT_TRUE(Intersects(a, b));
    EXPECT_FALSE(Intersects(b, c));
    EXPECT_FALSE(Intersects(a, c));
}

TEST(Intersections, AABBOBB)
{
    EXPECT_TRUE(false);
}

TEST(Intersections, OBBOBB)
{
    EXPECT_TRUE(false);
}

TEST(Intersections, PlaneAABB)
{
    const BoundsAABB boundsA(Vector3f( 10.0f,  10.0f,  10.0f), Vector3f(1.0f, 1.0f, 1.0f));
    const BoundsAABB boundsB(Vector3f(  0.0f,   0.0f,   0.0f), Vector3f(1.0f, 1.0f, 1.0f));
    const BoundsAABB boundsC(Vector3f(-10.0f, -10.0f, -10.0f), Vector3f(1.0f, 1.0f, 1.0f));

    const Plane plane(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));

    IntersectionType intersection;
    
    EXPECT_FALSE(Intersects(boundsA, plane, &intersection));
    EXPECT_EQ(intersection, IntersectionType::Outside);

    EXPECT_TRUE(Intersects(boundsB, plane, &intersection));
    EXPECT_EQ(intersection, IntersectionType::Intersects);

    EXPECT_FALSE(Intersects(boundsC, plane, &intersection));
    EXPECT_EQ(intersection, IntersectionType::Inside);
}

TEST(Intersections, PlaneOBB)
{
    EXPECT_TRUE(false);
}