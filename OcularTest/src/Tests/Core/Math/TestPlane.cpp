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
#include "gtest/gtest.h"

using namespace Ocular::Math;

//------------------------------------------------------------------------------------------

TEST(Plane, DistanceTo)
{
    const Plane plane(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));

    const Point3f pointA(0.0f, 10.0f, 0.0f);
    const Point3f pointB(0.0f, 0.0f, 10.0f);
    const Point3f pointC(5.0f, -3.0f, 0.0f);

    const float expectedA = 10.0f;
    const float expectedB =  0.0f;
    const float expectedC = -3.0f;

    const float resultA = plane.getSignedDistance(pointA);
    const float resultB = plane.getSignedDistance(pointB);
    const float resultC = plane.getSignedDistance(pointC);
    
    EXPECT_NEAR(resultA, expectedA, EPSILON_FLOAT);
    EXPECT_NEAR(resultB, expectedB, EPSILON_FLOAT);
    EXPECT_NEAR(resultC, expectedC, EPSILON_FLOAT);
}

TEST(Plane, GetClosest)
{
    const Plane plane(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));

    const Point3f pointA(0.0f, 10.0f, 0.0f);
    const Point3f pointB(0.0f, 0.0f, 10.0f);
    const Point3f pointC(5.0f, -3.0f, 0.0f);

    const Point3f expectedA(0.0f, 0.0f, 0.0f);
    const Point3f expectedB(0.0f, 0.0f, 10.0f);
    const Point3f expectedC(5.0f, 0.0f, 0.0f);

    const Point3f resultA = plane.getClosest(pointA);
    const Point3f resultB = plane.getClosest(pointB);
    const Point3f resultC = plane.getClosest(pointC);

    EXPECT_TRUE(resultA == expectedA);
    EXPECT_TRUE(resultB == expectedB);
    EXPECT_TRUE(resultC == expectedC);
}