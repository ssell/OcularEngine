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

#include "Math/Geometry/ConvexHull2D.hpp"
#include "gtest/gtest.h"

using namespace Ocular::Math;

//------------------------------------------------------------------------------------------

bool Contains(std::vector<Point2f> const& vector, Point2f const& point)
{
    bool result = false;

    if(std::find(vector.begin(), vector.end(), point) != vector.end())
    {
        result = true;
    }

    return result;
}

TEST(ConvexHull2D, Simple)
{
    // Triangle with a point in the center.
    std::vector<Point2f> points = 
    {
        Point2f(0.0f, 0.0f),
        Point2f(10.0f, 0.0f),
        Point2f(5.0f, 10.0f),
        Point2f(5.0f, 5.0f)
    };

    const ConvexHull2D convexHull(points);

    EXPECT_EQ(convexHull.getNumPoints(), 3);

    const std::vector<Point2f> hullPoints = convexHull.getHull();
    
    EXPECT_TRUE(Contains(hullPoints, Point2f(0.0f, 0.0f)));
    EXPECT_TRUE(Contains(hullPoints, Point2f(10.0f, 0.0f)));
    EXPECT_TRUE(Contains(hullPoints, Point2f(5.0f, 10.0f)));
}

TEST(ConvexHull2D, Complex)
{
    std::vector<Point2f> points = 
    {
        Point2f(-2.0f,  5.0f),
        Point2f( 2.0f,  5.0f),
        Point2f(-2.0f,  4.0f),
        Point2f(-1.0f,  4.0f),
        Point2f(-4.0f,  3.0f),
        Point2f( 2.0f,  3.0f),
        Point2f( 3.0f,  3.0f),
        Point2f( 1.0f,  2.0f),
        Point2f(-1.0f,  1.0f),
        Point2f(-3.0f,  0.0f),
        Point2f(-3.0f, -1.0f),
        Point2f( 1.0f, -1.0f),
        Point2f( 4.0f, -1.0f),
        Point2f(-1.0f, -2.0f)
    };

    const ConvexHull2D convexHull(points);

    EXPECT_EQ(convexHull.getNumPoints(), 7);

    const std::vector<Point2f> hullPoints = convexHull.getHull();
    
    EXPECT_TRUE(Contains(hullPoints, Point2f(-4.0f,  3.0f)));
    EXPECT_TRUE(Contains(hullPoints, Point2f(-2.0f,  5.0f)));
    EXPECT_TRUE(Contains(hullPoints, Point2f( 2.0f,  5.0f)));
    EXPECT_TRUE(Contains(hullPoints, Point2f( 3.0f,  3.0f)));
    EXPECT_TRUE(Contains(hullPoints, Point2f( 4.0f, -1.0f)));
    EXPECT_TRUE(Contains(hullPoints, Point2f(-1.0f, -2.0f)));
    EXPECT_TRUE(Contains(hullPoints, Point2f(-3.0f, -1.0f)));
}