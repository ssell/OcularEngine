/**
* Copyright 2014 Steven T Sell (ssell@ocularinteractive.com)
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
#include "gtest/gtest.h"

//------------------------------------------------------------------------------------------

Ocular::Math::Vector2d vecA(10.0, 8.0);
Ocular::Math::Vector2d vecB(33.0, 3.0);

TEST(MathVector2, Magnitude)
{
    double expected = 12.8062;
    double result = vecA.getMagnitude();

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}

TEST(MathVector2, Normalize)
{
    Ocular::Math::Vector2d expected(0.780869, 0.624695);
    Ocular::Math::Vector2d result = vecA.getNormalized();

    EXPECT_TRUE((expected == result));
}

TEST(MathVector2, DotProduct)
{
    double expected = 354.0;
    double result = vecA.dot(vecB);

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}

TEST(MathVector2, AngleBetween)
{
    double expected = 0.584081;
    double result = vecA.angleBetween(vecB);

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}

TEST(MathVector2, Distance)
{
    double expected = 23.5372;
    double result = vecA.distanceTo(vecB);

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}