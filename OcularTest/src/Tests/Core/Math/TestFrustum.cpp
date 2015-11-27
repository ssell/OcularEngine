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

#include "Math/Geometry/Frustum.hpp"
#include "gtest/gtest.h"

using namespace Ocular::Math;

//------------------------------------------------------------------------------------------

void CreateFrustum(Frustum& frustum)
{
    frustum.setView(Vector3f(0.0f, 0.0f, 0.0f), Vector3f::Forward(), Vector3f::Up());
    frustum.setProjectionPerspective(60.0f, (1024.0f / 768.0f), 10.0f, 100.0f);
    frustum.rebuild();
}

TEST(Frustum, ContainsPoint)
{
    Frustum frustum;
    CreateFrustum(frustum);

    //--------------------------------------------------------------------
    // Get various midpoints to test with

    auto nearCorners = frustum.getNearClipCorners();
    auto farCorners = frustum.getFarClipCorners();

    const Point3f leftMidpoint   = Vector3f::Midpoint(nearCorners[0], farCorners[3]);
    const Point3f rightMidpoint  = Vector3f::Midpoint(nearCorners[1], farCorners[2]);
    const Point3f topMidpoint    = Vector3f::Midpoint(nearCorners[3], farCorners[2]);
    const Point3f bottomMidpoint = Vector3f::Midpoint(nearCorners[0], farCorners[1]);
    const Point3f nearMidpoint   = Vector3f::Midpoint(nearCorners[0], nearCorners[2]);
    const Point3f farMidpoint    = Vector3f::Midpoint(farCorners[0], farCorners[2]);

    //--------------------------------------------------------------------
    // Setup inside/outside test

    const Point3f outsideLeft(leftMidpoint - Point3f(10.0f, 0.0f, 0.0f));
    const Point3f insideLeft(leftMidpoint + Point3f(10.0f, 0.0f, 0.0f));

    const Point3f outsideRight(rightMidpoint + Point3f(10.0f, 0.0f, 0.0f));
    const Point3f insideRight(rightMidpoint - Point3f(10.0f, 0.0f, 0.0f));

    const Point3f outsideTop(topMidpoint + Point3f(0.0f, 10.0f, 0.0f));
    const Point3f insideTop(topMidpoint - Point3f(0.0f, 10.0f, 0.0f));

    const Point3f outsideBottom(bottomMidpoint - Point3f(0.0f, 10.0f, 0.0f));
    const Point3f insideBottom(bottomMidpoint + Point3f(0.0f, 10.0f, 0.0f));

    const Point3f outsideNear(nearMidpoint + Vector3f(0.0f, 0.0f, 10.0f));
    const Point3f insideNear(nearMidpoint - Vector3f(0.0f, 0.0f, 10.0f));

    const Point3f outsideFar(farMidpoint - Vector3f(0.0f, 0.0f, 10.0f));
    const Point3f insideFar(farMidpoint + Vector3f(0.0f, 0.0f, 10.0f));

    //--------------------------------------------------------------------
    // Test inside/outside

    EXPECT_FALSE(frustum.contains(outsideNear));
    EXPECT_FALSE(frustum.contains(outsideFar));
    EXPECT_FALSE(frustum.contains(outsideLeft));
    EXPECT_FALSE(frustum.contains(outsideRight));
    EXPECT_FALSE(frustum.contains(outsideTop));
    EXPECT_FALSE(frustum.contains(outsideBottom));

    EXPECT_TRUE(frustum.contains(insideNear));
    EXPECT_TRUE(frustum.contains(insideFar));
    EXPECT_TRUE(frustum.contains(insideLeft));
    EXPECT_TRUE(frustum.contains(insideRight));
    EXPECT_TRUE(frustum.contains(insideTop));
    EXPECT_TRUE(frustum.contains(insideBottom));

    //--------------------------------------------------------------------
    // Test intersections using the 8 frustum corners, and the 6 side midpoints.

    EXPECT_TRUE(frustum.contains(nearCorners[0]));
    EXPECT_TRUE(frustum.contains(nearCorners[1]));
    EXPECT_TRUE(frustum.contains(nearCorners[2]));
    EXPECT_TRUE(frustum.contains(nearCorners[3]));
    EXPECT_TRUE(frustum.contains(farCorners[0]));
    EXPECT_TRUE(frustum.contains(farCorners[1]));
    EXPECT_TRUE(frustum.contains(farCorners[2]));
    EXPECT_TRUE(frustum.contains(farCorners[3]));

    EXPECT_TRUE(frustum.contains(leftMidpoint));
    EXPECT_TRUE(frustum.contains(rightMidpoint));
    EXPECT_TRUE(frustum.contains(topMidpoint));
    EXPECT_TRUE(frustum.contains(bottomMidpoint));
    EXPECT_TRUE(frustum.contains(nearMidpoint));
    EXPECT_TRUE(frustum.contains(farMidpoint));
}