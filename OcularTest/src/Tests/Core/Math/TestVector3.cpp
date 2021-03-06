/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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

#include "Math/Vector3.hpp"

#ifdef _DEBUG

#include "gtest/gtest.h"

//------------------------------------------------------------------------------------------

const Ocular::Math::Vector3d vecA(10.0, 10.0, 0.0);
const Ocular::Math::Vector3d vecB(33.0, 10.8, 3.0);

TEST(Vector3, VectorAddition)
{
    const Ocular::Math::Vector3d expected(43.0, 20.8, 3.0);
    const Ocular::Math::Vector3d result = vecA + vecB;

    EXPECT_TRUE((expected == result));
}

TEST(Vector3, ScalarAddition)
{
    const Ocular::Math::Vector3d expected(20.0, 20.0, 10.0);
    const Ocular::Math::Vector3d result = vecA + 10.0;

    EXPECT_TRUE((expected == result));
}

TEST(Vector3, VectorSubtraction)
{
    const Ocular::Math::Vector3d expected(-23.0, -0.8, -3.0);
    const Ocular::Math::Vector3d result = vecA - vecB;

    EXPECT_TRUE((expected == result));
}

TEST(Vector3, ScalarSubtraction)
{
    const Ocular::Math::Vector3d expected(0.0, 0.0, -10.0);
    const Ocular::Math::Vector3d result = vecA - 10.0;

    EXPECT_TRUE((expected == result));
}

TEST(Vector3, VectorMultiplication)
{
    const Ocular::Math::Vector3d expected(330.0, 108.0, 0.0);
    const Ocular::Math::Vector3d result = vecA * vecB;

    EXPECT_TRUE((expected == result));
}

TEST(Vector3, ScalarMultiplication)
{
    const Ocular::Math::Vector3d expected(100.0, 100.0, 0.0);
    const Ocular::Math::Vector3d result = vecA * 10.0;

    EXPECT_TRUE((expected == result));
}

TEST(Vector3, VectorDivision)
{
    const Ocular::Math::Vector3d expected(0.303030, 0.92592, 0.0);
    const Ocular::Math::Vector3d result = vecA / vecB;

    EXPECT_TRUE((expected == result));
}

TEST(Vector3, ScalarDivision)
{
    const Ocular::Math::Vector3d expected(1.0, 1.0, 0.0);
    const Ocular::Math::Vector3d result = vecA / 10.0;

    EXPECT_TRUE((expected == result));
}

TEST(Vector3, Magnitude)
{
    const double expected = 14.1421;
    const double result = vecA.getMagnitude();

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}

TEST(Vector3, Normalize)
{
    const Ocular::Math::Vector3d expected(0.7071, 0.7071, 0.0);
    const Ocular::Math::Vector3d result = vecA.getNormalized();
    
    EXPECT_TRUE((expected == result));
}

TEST(Vector3, CrossProduct)
{
    const Ocular::Math::Vector3d expected(30.0, -30.0, -222.0);
    const Ocular::Math::Vector3d result = vecA.cross(vecB);
    
    EXPECT_TRUE((expected == result));
}

TEST(Vector3, DotProduct)
{
    const double expected = 438.0;
    const double result = vecA.dot(vecB);

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}

TEST(Vector3, AngleBetween)
{
    const double expected = 0.476383;
    const double result = vecA.angleBetween(vecB);

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}

TEST(Vector3, Distance)
{
    const double expected = 23.2086;
    const double result = vecA.distanceTo(vecB);

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}

TEST(Vector3, Midpoint)
{
    const Ocular::Math::Vector3d expected = Ocular::Math::Vector3d(21.5, 10.4, 1.5);
    const Ocular::Math::Vector3d result = Ocular::Math::Vector3d::Midpoint(vecA, vecB);
    
    EXPECT_TRUE((expected == result));
}

TEST(Vector3, Lerp)
{
    const Ocular::Math::Vector3d midpoint = Ocular::Math::Vector3d::Midpoint(vecA, vecB);

    const Ocular::Math::Vector3d resultZero = Ocular::Math::Vector3d::Lerp(vecA, vecB, 0.0);
    const Ocular::Math::Vector3d resultHalf = Ocular::Math::Vector3d::Lerp(vecA, vecB, 0.5);
    const Ocular::Math::Vector3d resultOne  = Ocular::Math::Vector3d::Lerp(vecA, vecB, 1.0);

    EXPECT_TRUE((vecA == resultZero));
    EXPECT_TRUE((midpoint == resultHalf));
    EXPECT_TRUE((vecB == resultOne));
}

#endif