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

#include "Math/Bounds/Ray.hpp"
#include "Math/Bounds/BoundsSphere.hpp"
#include "Math/Bounds/BoundsAABB.hpp"
#include "Math/Bounds/BoundsOBB.hpp"
#include "Math/Geometry/Plane.hpp"

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

    EXPECT_TRUE(goodRay.intersects(sphere, intersectionPoint, intersectionDistance));
    EXPECT_TRUE((intersectionPoint == Vector3f(5.0f, 0.0f, 0.0f)));
    EXPECT_NEAR(intersectionDistance, 5.0f, EPSILON_FLOAT);

    EXPECT_FALSE(badRay.intersects(sphere));
}

TEST(Intersections, RayAABB)
{
    const BoundsAABB aabb(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(5.0f, 5.0f, 5.0f));

    const Ray goodRay(Vector3f(10.0f, 0.0f, 0.0f), Vector3f(-1.0f, 0.0f, 0.0f));
    const Ray badRay(Vector3f(100.0f, 100.0f, 0.0f), Vector3f(-1.0f, 0.0f, 0.0f));

    Vector3f intersectionPoint;
    float intersectionDistance;

    EXPECT_TRUE(goodRay.intersects(aabb, intersectionPoint, intersectionDistance));
    EXPECT_TRUE((intersectionPoint == Vector3f(5.0f, 0.0f, 0.0f)));
    EXPECT_NEAR(intersectionDistance, 5.0f, EPSILON_FLOAT);

    EXPECT_FALSE(badRay.intersects(aabb));
}

TEST(Intersections, RayOBB)
{
    EXPECT_TRUE(false);
}

TEST(Intersections, RayPlane)
{
    const Plane planeA(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
    const Plane planeB(Vector3f(10.0f, 10.0f, 10.0f), Vector3f(1.0f, 0.0f, 0.0f));

    const Ray rayA(Vector3f(0.0f, 10.0f, 0.0f), Vector3f(0.0f, -1.0f, 0.0f));
    const Ray rayB(Vector3f(-10.0f, 0.0f, 0.0f), Vector3f(1.0f, 0.0f, 0.0f));

    Point3f point;
    float distance;

    EXPECT_TRUE(rayA.intersects(planeA, point, distance));
    EXPECT_NEAR(distance, 10.0f, EPSILON_FLOAT);
    EXPECT_EQ(point, Vector3f(0.0f, 0.0f, 0.0f));

    EXPECT_FALSE(rayA.intersects(planeB));
    
    EXPECT_TRUE(rayB.intersects(planeB, point, distance));
    EXPECT_NEAR(distance, 20.0f, EPSILON_FLOAT);
    EXPECT_EQ(point, Vector3f(10.0f, 0.0f, 0.0f));

    EXPECT_FALSE(rayB.intersects(planeA));
}

TEST(Intersections, SphereSphere)
{
    const BoundsSphere a(Vector3f(0.0f, 0.0f, 0.0f), 10.0f);
    const BoundsSphere b(Vector3f(5.0f, 0.0f, 0.0f), 1.0f);
    const BoundsSphere c(Vector3f(20.0f, 20.0f, 20.0f), 1.0f);
    const BoundsSphere d(Vector3f(15.0f, 0.0f, 0.0f), 10.0f);
    
    EXPECT_TRUE(a.intersects(b));
    EXPECT_TRUE(a.intersects(d));
    EXPECT_FALSE(a.intersects(c));
    EXPECT_FALSE(b.intersects(c));
}

TEST(Intersections, SphereAABB)
{
    const BoundsSphere sphere(Vector3f(0.0f, 0.0f, 0.0f), 10.0f);
    const BoundsAABB aabbA(Vector3f(12.0f, 0.0f, 0.0f), Vector3f(5.0f, 5.0f, 5.0f));
    const BoundsAABB aabbB(Vector3f(30.0f, 0.0f, 0.0f), Vector3f(10.0f, 10.0f, 10.0f));

    EXPECT_TRUE(sphere.intersects(aabbA));
    EXPECT_FALSE(sphere.intersects(aabbB));
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

    EXPECT_TRUE(a.intersects(b));
    EXPECT_FALSE(b.intersects(c));
    EXPECT_FALSE(a.intersects(c));
}

TEST(Intersections, AABBOBB)
{
    EXPECT_TRUE(false);
}

TEST(Intersections, OBBOBB)
{
    EXPECT_TRUE(false);
}

TEST(Intersections, PlaneSphere)
{
    const Plane plane(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
    
    const BoundsSphere boundsA(Vector3f(0.0f, 10.0f, 0.0f), 5.0f);
    const BoundsSphere boundsB(Vector3f(0.0f, 5.0f, 0.0f), 5.0f);
    const BoundsSphere boundsC(Vector3f(-3.0f, -3.0f, 0.0f), 5.0f);
    const BoundsSphere boundsD(Vector3f(10.0f, -10.0f, 10.0f), 5.0f);

    IntersectionType intersection;

    EXPECT_FALSE(plane.intersects(boundsA, &intersection));
    EXPECT_EQ(intersection, IntersectionType::Outside);

    EXPECT_TRUE(plane.intersects(boundsB, &intersection));
    EXPECT_EQ(intersection, IntersectionType::Intersects);

    EXPECT_TRUE(plane.intersects(boundsC, &intersection));
    EXPECT_EQ(intersection, IntersectionType::Intersects);

    EXPECT_FALSE(plane.intersects(boundsD, &intersection));
    EXPECT_EQ(intersection, IntersectionType::Inside);
    
}

TEST(Intersections, PlaneAABB)
{
    const BoundsAABB boundsA(Vector3f( 10.0f,  10.0f,  10.0f), Vector3f(1.0f, 1.0f, 1.0f));
    const BoundsAABB boundsB(Vector3f(  0.0f,   0.0f,   0.0f), Vector3f(1.0f, 1.0f, 1.0f));
    const BoundsAABB boundsC(Vector3f(-10.0f, -10.0f, -10.0f), Vector3f(1.0f, 1.0f, 1.0f));

    const Plane plane(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));

    IntersectionType intersection;
    
    EXPECT_FALSE(plane.intersects(boundsA, &intersection));
    EXPECT_EQ(intersection, IntersectionType::Outside);

    EXPECT_TRUE(plane.intersects(boundsB, &intersection));
    EXPECT_EQ(intersection, IntersectionType::Intersects);

    EXPECT_FALSE(plane.intersects(boundsC, &intersection));
    EXPECT_EQ(intersection, IntersectionType::Inside);
}

TEST(Intersections, PlaneOBB)
{
    EXPECT_TRUE(false);
}