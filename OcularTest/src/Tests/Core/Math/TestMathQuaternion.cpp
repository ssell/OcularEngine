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
    const Quaternion a(1.0f, 0.0f, 1.0f, 0.0f);
    const Quaternion b(0.0f, 1.0f, 0.0f, 1.0f);
    const Quaternion c(1.0f, 0.0f, 1.0f, 0.0f);

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
    EXPECT_TRUE(a == c);
    EXPECT_FALSE(a != c);
}

TEST(Quaternion, Addition)
{
    const Quaternion a(1.0f, 0.0f, 1.0f, 0.0f);
    const Quaternion b(0.0f, 1.0f, 0.0f, 1.0f);
    const Quaternion c(1.0f, 1.0f, 1.0f, 1.0f);
    const Quaternion d = a + b;

    EXPECT_TRUE(c == d);
}

TEST(Quaternion, Subtraction)
{
    const Quaternion a(1.0f, 0.0f, 1.0f, 0.0f);
    const Quaternion b(0.0f, 1.0f, 0.0f, 1.0f);
    const Quaternion c(1.0f, -1.0f, 1.0f, -1.0f);
    const Quaternion d = a - b;

    EXPECT_TRUE(c == d);
}

TEST(Quaternion, Multiplication)
{
    const Quaternion a(1.0f, 0.5f, 0.25f, -0.1f);
    const Quaternion b(-0.1f, 0.25f, 0.5f, 1.0f);
    const Quaternion ab = a * b;
    
    EXPECT_NEAR(ab.w, -0.25f,   EPSILON_FLOAT);
    EXPECT_NEAR(ab.x,  0.5f,    EPSILON_FLOAT);
    EXPECT_NEAR(ab.y, -0.05f,   EPSILON_FLOAT);
    EXPECT_NEAR(ab.z,  1.1975f, EPSILON_FLOAT);
}

TEST(Quaternion, Division)
{
    const Quaternion a(1.0f, 0.5f, 0.25f, -0.1f);
    const Quaternion b = a / 0.5f;
    
    EXPECT_NEAR(b.w,  2.0f, EPSILON_FLOAT);
    EXPECT_NEAR(b.x,  1.0f, EPSILON_FLOAT);
    EXPECT_NEAR(b.y,  0.5f, EPSILON_FLOAT);
    EXPECT_NEAR(b.z, -0.2f, EPSILON_FLOAT);
}

TEST(Quaternion, Normalize)
{
    const Quaternion quat(13.2f, 22.84f, 1.0f, -0.88f);
    const Quaternion norm = quat.getNormalized();
    
    EXPECT_NEAR(norm.w,  0.499741882f, EPSILON_FLOAT);
    EXPECT_NEAR(norm.x,  0.864704907f, EPSILON_FLOAT);
    EXPECT_NEAR(norm.y,  0.037859235f, EPSILON_FLOAT);
    EXPECT_NEAR(norm.z, -0.033316128f, EPSILON_FLOAT);
}

TEST(Quaternion, Rotate)
{
    // Tests rotating a Vector by a Quaternion

    // TODO

    EXPECT_TRUE(false);
}

TEST(Quaternion, Length)
{
    const Quaternion quat(13.2f, 22.84f, 1.0f, -0.88f);
    const float length = quat.getLength();

    EXPECT_NEAR(length, 26.4136333f, EPSILON_FLOAT);
}

TEST(Quaternion, Inverse)
{
    const Quaternion quat(13.2f, 22.84f, 1.0f, -0.88f);
    const Quaternion inverse = quat.getInverse();
    
    EXPECT_NEAR(inverse.w,  0.0189198479f,  EPSILON_FLOAT);
    EXPECT_NEAR(inverse.x, -0.0327370726f,  EPSILON_FLOAT);
    EXPECT_NEAR(inverse.y, -0.00143332186f, EPSILON_FLOAT);
    EXPECT_NEAR(inverse.z,  0.00126132322f, EPSILON_FLOAT);
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
    Quaternion quatA(10.2f, 20.84f, 0.0f, -0.08f);
    Quaternion quatB(13.2f, 22.84f, 1.0f, -0.88f);
    Quaternion quatC;

    quatA.normalize();
    quatB.normalize();
    quatC = Quaternion::lerp(quatA, quatB, 0.695f);
    
    EXPECT_NEAR(quatC.w,  0.481401503f,  EPSILON_FLOAT);
    EXPECT_NEAR(quatC.x,  0.874915540f,  EPSILON_FLOAT);
    EXPECT_NEAR(quatC.y,  0.0263121687f, EPSILON_FLOAT);
    EXPECT_NEAR(quatC.z, -0.0242063235f, EPSILON_FLOAT);
}

TEST(Quaternion, Bilerp)
{
    // Tests performing Quaternion bilinear interpolation

    // TODO

    EXPECT_TRUE(false);
}

TEST(Quaternion, Slerp)
{
    Quaternion quatA(10.2f, 20.84f, 0.0f, -0.08f);
    Quaternion quatB(13.2f, 22.84f, 1.0f, -0.88f);
    Quaternion quatC;

    quatA.normalize();
    quatB.normalize();
    quatC = Quaternion::slerp(quatA, quatB, 0.695f);
    
    EXPECT_NEAR(quatC.w,  0.481756449f,  EPSILON_FLOAT);
    EXPECT_NEAR(quatC.x,  0.875574708f,  EPSILON_FLOAT);
    EXPECT_NEAR(quatC.y,  0.0263282005f, EPSILON_FLOAT);
    EXPECT_NEAR(quatC.z, -0.0242215563f, EPSILON_FLOAT);
}
