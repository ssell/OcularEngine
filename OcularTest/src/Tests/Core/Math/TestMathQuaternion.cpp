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

#include "Math/Quaternion.hpp"
#include "gtest/gtest.h"

using namespace Ocular::Math;

//------------------------------------------------------------------------------------------

TEST(Quaternion, Equality)
{
    Quaternion a(1.0f, 0.0f, 1.0f, 0.0f);
    Quaternion b(0.0f, 1.0f, 0.0f, 1.0f);
    Quaternion c(1.0f, 0.0f, 1.0f, 0.0f);

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
    EXPECT_TRUE(a == c);
    EXPECT_FALSE(a != c);
}

TEST(Quaternion, Addition)
{
    Quaternion a(1.0f, 0.0f, 1.0f, 0.0f);
    Quaternion b(0.0f, 1.0f, 0.0f, 1.0f);
    Quaternion c(1.0f, 1.0f, 1.0f, 1.0f);
    Quaternion d = a + b;

    EXPECT_TRUE(c == d);
}

TEST(Quaternion, Subtraction)
{
    Quaternion a(1.0f, 0.0f, 1.0f, 0.0f);
    Quaternion b(0.0f, 1.0f, 0.0f, 1.0f);
    Quaternion c(1.0f, -1.0f, 1.0f, -1.0f);
    Quaternion d = a - b;

    EXPECT_TRUE(c == d);
}

TEST(Quaternion, Multiplication)
{
    // TODO
    EXPECT_TRUE(false);
}

TEST(Quaternion, Division)
{
    // TODO
    EXPECT_TRUE(false);
}

TEST(Quaternion, Normalize)
{
    // Tests the following Quaternion normalization functions:
    //     normalize, getNormalized, isNormalized

    // TODO

    EXPECT_TRUE(false);
}

TEST(Quaternion, Rotate)
{
    // Tests rotating a Vector by a Quaternion

    // TODO

    EXPECT_TRUE(false);
}

TEST(Quaternion, Length)
{
    // Tests the following Quaternion length functions:
    //     getLength, getLengthSquared

    // TODO

    EXPECT_TRUE(false);
}

TEST(Quaternion, Inverse)
{
    // Tests calculating the inverse of a Quaternion

    // TODO

    EXPECT_TRUE(false);
}

TEST(Quaternion, GetRotation)
{
    // Tests the following Quaternion rotation axis functions:
    //     getXRotationAxis, getYRotationAxis, getZRotationAxis, getRotationAxis

    // TODO

    EXPECT_TRUE(false);
}

TEST(Quaternion, Lerp)
{
    // Tests performing Quaternion linear interpolation

    // TODO

    EXPECT_TRUE(false);
}

TEST(Quaternion, Bilerp)
{
    // Tests performing Quaternion bilinear interpolation

    // TODO

    EXPECT_TRUE(false);
}

TEST(Quaternion, Slerp)
{
    // Tests perfoming Quaternion spherical linear interpolation

    // TODO

    EXPECT_TRUE(false);
}
