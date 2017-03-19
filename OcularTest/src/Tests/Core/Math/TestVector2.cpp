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

#include "Math/Vector2.hpp"

#ifdef _DEBUG

#include "gtest/gtest.h"

//------------------------------------------------------------------------------------------

const Ocular::Math::Vector2d vecA(10.0, 8.0);
const Ocular::Math::Vector2d vecB(33.0, 3.0);

TEST(Vector2, VectorAddition)
{
    const Ocular::Math::Vector2d expected(43.0, 11.0);
    const Ocular::Math::Vector2d result = vecA + vecB;

    EXPECT_TRUE((expected == result));
}

TEST(Vector2, ScalarAddition)
{
    const Ocular::Math::Vector2d expected(20.0, 18.0);
    const Ocular::Math::Vector2d result = vecA + 10.0;

    EXPECT_TRUE((expected == result));
}

TEST(Vector2, VectorSubtraction)
{
    const Ocular::Math::Vector2d expected(-23.0, 5.0);
    const Ocular::Math::Vector2d result = vecA - vecB;

    EXPECT_TRUE((expected == result));
}

TEST(Vector2, ScalarSubtraction)
{
    const Ocular::Math::Vector2d expected(0.0, -2.0);
    const Ocular::Math::Vector2d result = vecA - 10.0;

    EXPECT_TRUE((expected == result));
}

TEST(Vector2, VectorMultiplication)
{
    const Ocular::Math::Vector2d expected(330.0, 24.0);
    const Ocular::Math::Vector2d result = vecA * vecB;

    EXPECT_TRUE((expected == result));
}

TEST(Vector2, ScalarMultiplication)
{
    const Ocular::Math::Vector2d expected(100.0, 80.0);
    const Ocular::Math::Vector2d result = vecA * 10.0;

    EXPECT_TRUE((expected == result));
}

TEST(Vector2, VectorDivision)
{
    const Ocular::Math::Vector2d expected(0.303030, 2.666667);
    const Ocular::Math::Vector2d result = vecA / vecB;

    EXPECT_TRUE((expected == result));
}

TEST(Vector2, ScalarDivision)
{
    const Ocular::Math::Vector2d expected(1.0, 0.8);
    const Ocular::Math::Vector2d result = vecA / 10.0;

    EXPECT_TRUE((expected == result));
}

TEST(Vector2, Magnitude)
{
    const double expected = 12.8062;
    const double result = vecA.getMagnitude();

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}

TEST(Vector2, Normalize)
{
    const Ocular::Math::Vector2d expected(0.780869, 0.624695);
    const Ocular::Math::Vector2d result = vecA.getNormalized();

    EXPECT_TRUE((expected == result));
}

TEST(Vector2, DotProduct)
{
    const double expected = 354.0;
    const double result = vecA.dot(vecB);

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}

TEST(Vector2, AngleBetween)
{
    const double expected = 0.584081;
    const double result = vecA.angleBetween(vecB);

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}

TEST(Vector2, Distance)
{
    const double expected = 23.5372;
    const double result = vecA.distanceTo(vecB);

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}

#endif