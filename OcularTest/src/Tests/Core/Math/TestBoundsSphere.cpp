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

#include "Math/Bounds/BoundsSphere.hpp"
#include "gtest/gtest.h"

using namespace Ocular::Math;

//------------------------------------------------------------------------------------------

TEST(BoundsSphere, SetCenter)
{
    BoundsSphere sphere(Vector3f(0.0f, 0.0f, 0.0f), 1.0f);

    const Vector3f expectA(0.0f, 0.0f, 0.0f);
    const Vector3f expectB(1.0f, 1.0f, 1.0f);

    EXPECT_TRUE(sphere.getCenter() == expectA);

    sphere.setCenter(expectB);

    EXPECT_TRUE(sphere.getCenter() == expectB);
}

TEST(BoundsSphere, SetRadius)
{
    BoundsSphere sphere(Vector3f(0.0f, 0.0f, 0.0f), 1.0f);

    const float expectA = 1.0f;
    const float expectB = 10.0f;
    const float expectC = 0.0f;
    
    EXPECT_NEAR(sphere.getRadius(), expectA, EPSILON_FLOAT);

    sphere.setRadius(expectB);

    EXPECT_NEAR(sphere.getRadius(), expectB, EPSILON_FLOAT);

    sphere.setRadius(-10.0f);

    EXPECT_NEAR(sphere.getRadius(), expectC, EPSILON_FLOAT);
}

TEST(BoundsSphere, Construct)
{
    const std::list<Point3f> points =
    {
        Point3f(-2.0f, 0.0f, 0.0f),
        Point3f(0.0f, 0.0f, 0.0f),
        Point3f(1.0f, 0.0f, 0.0f)
    };

    const BoundsSphere sphere(points);

    const Point3f expectedCenter(-0.5f, 0.0f, 0.0f);
    const float expectedRadius = 1.5f;

    EXPECT_TRUE(sphere.getCenter() == expectedCenter);
    EXPECT_NEAR(sphere.getRadius(), expectedRadius, EPSILON_FLOAT);
}

TEST(BoundsSphere, ExpandRadius)
{
    BoundsSphere sphere(Vector3f(0.0f, 0.0f, 0.0f), 1.0f);

    const float expectA = 2.0f;
    const float expectB = 0.0f;
    
    sphere.expand(1.0f);

    EXPECT_NEAR(sphere.getRadius(), expectA, EPSILON_FLOAT);

    sphere.expand(-3.0f);

    EXPECT_NEAR(sphere.getRadius(), expectB, EPSILON_FLOAT);
}

TEST(BoundsSphere, ExpandToPoint)
{
    BoundsSphere sphere(Vector3f(0.0f, 0.0f, 0.0f), 1.0f);
    const Point3f point(2.0f, 0.0f, 0.0f);

    const Point3f expectedCenter(0.5f, 0.0f, 0.0f);
    const float   expectedRadius = 1.5f;

    sphere.expandToContain(point);

    EXPECT_TRUE(sphere.getCenter() == expectedCenter);
    EXPECT_NEAR(sphere.getRadius(), expectedRadius, EPSILON_FLOAT);
}

TEST(BoundsSphere, ContainsPoint)
{
    const BoundsSphere sphere(Vector3f(0.0f, 0.0f, 0.0f), 1.0f);

    const Point3f pointA(0.0f, 0.0f, 0.0f);
    const Point3f pointB(1.0f, 0.0f, 0.0f);
    const Point3f pointC(2.0f, 0.0f, 0.0f);

    IntersectionType result;

    EXPECT_TRUE(sphere.contains(pointA, &result));
    EXPECT_EQ(result, IntersectionType::Inside);

    EXPECT_TRUE(sphere.contains(pointB, &result));
    EXPECT_EQ(result, IntersectionType::Intersects);

    EXPECT_FALSE(sphere.contains(pointC, &result));
    EXPECT_EQ(result, IntersectionType::Outside);
}

TEST(BoundsSphere, ContainsSphere)
{
    const BoundsSphere sphere(Vector3f(0.0f, 0.0f, 0.0f), 10.0f);

    const BoundsSphere sphereA(Vector3f(0.0f, 0.0f, 0.0f), 1.0f);
    const BoundsSphere sphereB(Vector3f(9.0f, 0.0f, 0.0f), 1.0f);
    const BoundsSphere sphereC(Vector3f(11.0f, 0.0f, 0.0f), 1.0f);
    const BoundsSphere sphereD(Vector3f(20.0f, 0.0f, 0.0f), 20.0f);
    const BoundsSphere sphereE(Vector3f(20.0f, 0.0f, 0.0f), 1.0f);

    IntersectionType result;

    EXPECT_TRUE(sphere.contains(sphereA, &result));
    EXPECT_EQ(result, IntersectionType::Inside);

    EXPECT_TRUE(sphere.contains(sphereB, &result));
    EXPECT_EQ(result, IntersectionType::Intersects);

    EXPECT_TRUE(sphere.contains(sphereC, &result));
    EXPECT_EQ(result, IntersectionType::Intersects);

    EXPECT_TRUE(sphere.contains(sphereD, &result));
    EXPECT_EQ(result, IntersectionType::Intersects);

    EXPECT_FALSE(sphere.contains(sphereE, &result));
    EXPECT_EQ(result, IntersectionType::Outside);
}