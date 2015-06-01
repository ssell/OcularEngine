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

#include "Math/BoundsAABB.hpp"
#include "gtest/gtest.h"

using namespace Ocular::Math;

//------------------------------------------------------------------------------------------

TEST(BoundsAABB, SetCenter)
{
    BoundsAABB aabb(Vector3f(1.0f, 1.0f, 1.0f), Vector3f(1.0f, 1.0f, 1.0f));

    EXPECT_TRUE(aabb.getCenter() == Vector3f(1.0f, 1.0f, 1.0f));

    aabb.setCenter(Vector3f(0.0f, 0.0f, 0.0f));

    EXPECT_TRUE(aabb.getCenter() == Vector3f(0.0f, 0.0f, 0.0f));
}

TEST(BoundsAABB, SetExtents)
{
    BoundsAABB aabb(Vector3f(1.0f, 1.0f, 1.0f), Vector3f(1.0f, 1.0f, 1.0f));

    EXPECT_TRUE(aabb.getExtents() == Vector3f(1.0f, 1.0f, 1.0f));

    aabb.setExtents(Vector3f(2.0f, 2.0f, 2.0f));

    EXPECT_TRUE(aabb.getExtents() == Vector3f(2.0f, 2.0f, 2.0f));
}

TEST(BoundsAABB, GetMinPoint)
{
    BoundsAABB aabb(Vector3f(1.0f, 1.0f, 1.0f), Vector3f(1.0f, 1.0f, 1.0f));

    const Vector3f aabbMin  = aabb.getMinPoint();
    const Vector3f expected = Vector3f(0.0f, 0.0f, 0.0f);

    EXPECT_TRUE(aabbMin == expected);
}

TEST(BoundsAABB, GetMaxPoint)
{
    BoundsAABB aabb(Vector3f(1.0f, 1.0f, 1.0f), Vector3f(1.0f, 1.0f, 1.0f));

    const Vector3f aabbMax  = aabb.getMaxPoint();
    const Vector3f expected = Vector3f(2.0f, 2.0f, 2.0f);

    EXPECT_TRUE(aabbMax == expected);
}

TEST(BoundsAABB, Expand)
{
    BoundsAABB aabb(Vector3f(1.0f, 1.0f, 1.0f), Vector3f(1.0f, 1.0f, 1.0f));

    const Vector3f extentsA(2.0f, 2.0f, 2.0f);
    const Vector3f extentsB(1.5f, 1.5f, 1.5f);
    const Vector3f extentsC(0.0f, 1.5f, 1.5f);

    aabb.expand(Vector3f(1.0f, 1.0f, 1.0f));

    EXPECT_TRUE(aabb.getExtents() == extentsA);

    aabb.expand(Vector3f(-0.5f, -0.5f, -0.5f));

    EXPECT_TRUE(aabb.getExtents() == extentsB);

    aabb.expand(Vector3f(-10.0f, 0.0f, 0.0f));

    EXPECT_TRUE(aabb.getExtents() == extentsC);
}

TEST(BoundsAABB, ExpandToPoint)
{
    BoundsAABB aabb(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));

    const Point3f pointA(0.0f, 0.0f, 0.0f);
    const Point3f pointB(2.0f, 2.0f, 2.0f);

    const Vector3f centerA(0.0f, 0.0f, 0.0f);
    const Vector3f centerB(0.5f, 0.5f, 0.5f);
    
    const Vector3f extentsA(1.0f, 1.0f, 1.0f);
    const Vector3f extentsB(1.5f, 1.5f, 1.5f);

    aabb.expandToContain(pointA);

    EXPECT_TRUE(aabb.getCenter() == centerA);
    EXPECT_TRUE(aabb.getExtents() == extentsA);

    aabb.expandToContain(pointB);

    EXPECT_TRUE(aabb.getCenter() == centerB);
    EXPECT_TRUE(aabb.getExtents() == extentsB);
}

TEST(BoundsAABB, ExpandToAABB)
{
    BoundsAABB aabbA(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
    BoundsAABB aabbB(Vector3f(1.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
    BoundsAABB aabbC(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.5f, 0.5f, 0.5f));

    const Point3f center(0.5f, 0.0f, 0.0f);
    const Point3f extents(1.5f, 1.0f, 1.0f);

    aabbA.expandToContain(aabbB);

    EXPECT_TRUE(aabbA.getCenter() == center);
    EXPECT_TRUE(aabbA.getExtents() == extents);

    aabbA.expandToContain(aabbC);

    EXPECT_TRUE(aabbA.getCenter() == center);    // aabbC is inside aabbA so no change is expected
    EXPECT_TRUE(aabbA.getExtents() == extents);
}

TEST(BoundsAABB, ContainsPoint)
{
    const BoundsAABB aabb(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));

    const Point3f pointA(0.0f, 0.0f, 0.0f);
    const Point3f pointB(1.0f, 0.0f, 0.0f);
    const Point3f pointC(0.0f, 0.0f, -1.0f);
    const Point3f pointD(0.0f, 0.0f, 10.0f);

    ContainsResult result;

    EXPECT_TRUE(aabb.contains(pointA, &result));
    EXPECT_EQ(result, ContainsResult::Inside);
    
    EXPECT_TRUE(aabb.contains(pointB, &result));
    EXPECT_EQ(result, ContainsResult::Inside);

    EXPECT_TRUE(aabb.contains(pointB, &result, true));
    EXPECT_EQ(result, ContainsResult::Intersects);

    EXPECT_TRUE(aabb.contains(pointC, &result, true));
    EXPECT_EQ(result, ContainsResult::Intersects);

    EXPECT_FALSE(aabb.contains(pointD, &result));
    EXPECT_EQ(result, ContainsResult::Outside);
}

TEST(BoundsAABB, ContainsAABB)
{
    const BoundsAABB aabbA(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
    const BoundsAABB aabbB(Vector3f(1.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
    const BoundsAABB aabbC(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.5f, 0.5f, 0.5f));
    const BoundsAABB aabbD(Vector3f(5.0f, 5.0f, 5.0f), Vector3f(1.0f, 1.0f, 1.0f));

    ContainsResult result;

    EXPECT_TRUE(aabbA.contains(aabbB, &result, true));
    EXPECT_EQ(result, ContainsResult::Intersects);

    EXPECT_TRUE(aabbA.contains(aabbC, &result));
    EXPECT_EQ(result, ContainsResult::Inside);

    EXPECT_FALSE(aabbA.contains(aabbD, &result));
    EXPECT_EQ(result, ContainsResult::Outside);
}

TEST(BoundsAABB, Construct)
{
    std::list<Point3f> points =
    {
        Point3f(0.0f, 0.0f, 0.0f),
        Point3f(5.0f, 4.0f, 3.0f),
        Point3f(-1.0f, 5.0f, -5.0f),
        Point3f(-5.0f, 0.0f, 5.0f),
        Point3f(0.0f, -5.0f, 1.0f)
    };

    const BoundsAABB aabb(points);

    const Vector3f center(0.0f, 0.0f, 0.0f);
    const Vector3f extents(5.0f, 5.0f, 5.0f);

    EXPECT_TRUE(aabb.getCenter() == center);
    EXPECT_TRUE(aabb.getExtents() == extents);
}
