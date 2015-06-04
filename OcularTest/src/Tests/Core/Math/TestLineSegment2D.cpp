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

#include "Math/LineSegment2D.hpp"
#include "gtest/gtest.h"

using namespace Ocular::Math;

const int32_t LEFT    = 1;
const int32_t RIGHT   = -1;
const int32_t ON_LINE = 0;

//------------------------------------------------------------------------------------------

TEST(LineSegment2D, SetEndPoints)
{
    LineSegment2Df segment(Point2f(0.0f, 0.0f), Point2f(10.0f, 0.0f));

    const Point2f expectedA0(0.0f, 0.0f);
    const Point2f expectedB0(10.0f, 0.0f);

    const Point2f expectedA1(10.0f, 0.0f);
    const Point2f expectedB1(10.0f, 5.0f);

    EXPECT_TRUE(segment.getA() == expectedA0);
    EXPECT_TRUE(segment.getB() == expectedB0);

    segment.setA(expectedA1);
    segment.setB(expectedB1);

    EXPECT_TRUE(segment.getA() == expectedA1);
    EXPECT_TRUE(segment.getB() == expectedB1);
}

TEST(LineSegment2D, GetLength)
{
    LineSegment2Df segment(Point2f(0.0f, 0.0f), Point2f(10.0f, 0.0f));

    const float expectedLength0 = 10.0f;
    const float expectedLengthSquared0 = 100.0f;

    const float expectedLength1 = 5.0f;
    const float expectedLengthSquared1 = 25.0f;

    EXPECT_NEAR(segment.getLength(), expectedLength0, EPSILON_FLOAT);
    EXPECT_NEAR(segment.getLengthSquared(), expectedLengthSquared0, EPSILON_FLOAT);

    segment.setA(Point2f(5.0f, 0.0f));

    EXPECT_NEAR(segment.getLength(), expectedLength1, EPSILON_FLOAT);
    EXPECT_NEAR(segment.getLengthSquared(), expectedLengthSquared1, EPSILON_FLOAT);
}

TEST(LineSegment2D, WhichSide)
{
    LineSegment2Df segment(Point2f(0.0f, 0.0f), Point2f(10.0f, 0.0f));

    const Point2f point0(5.0f,  5.0f);
    const Point2f point1(5.0f, -5.0f);
    const Point2f point2(5.0f,  0.0f);
    
    EXPECT_TRUE(segment.whichSide(point0) == LEFT);
    EXPECT_TRUE(segment.whichSide(point1) == RIGHT);

    segment.setA(Point2f(10.0f, 0.0f));               // Reverse the direction of the segment
    segment.setB(Point2f(0.0f, 0.0f));

    EXPECT_TRUE(segment.whichSide(point0) == RIGHT);  // What was on the left, should now be on the right
    EXPECT_TRUE(segment.whichSide(point1) == LEFT);
    EXPECT_TRUE(segment.whichSide(point2) == ON_LINE);
}

TEST(LineSegment2D, DistanceTo)
{
    const LineSegment2Df segment(Point2f(0.0f, 0.0f), Point2f(10.0f, 0.0f));

    const Point2f point0(0.0f, 5.0f);
    const Point2f point1(5.0f, 8.0f);
    const Point2f point2(10.0f, 7.0f);

    const float expected0 = 5.0f;
    const float expected1 = 8.0f;
    const float expected2 = -7.0f;
    
    const float result0 = segment.distanceTo(point0);
    const float result1 = segment.distanceTo(point1);
    const float result2 = segment.distanceTo(point2);

    EXPECT_NEAR(result0, expected0, EPSILON_FLOAT);
    EXPECT_NEAR(result1, expected1, EPSILON_FLOAT);
    EXPECT_NEAR(result2, expected2, EPSILON_FLOAT);
}