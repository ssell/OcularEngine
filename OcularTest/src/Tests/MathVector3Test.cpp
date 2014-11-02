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

#include "Math/Vector3.hpp"
#include "gtest/gtest.h"

//------------------------------------------------------------------------------------------

TEST(MathVector3, Magnitude)
{
    Ocular::Math::Vector3d vecA(10.0, 10.0, 0.0);

    double expected = 14.1421;
    double result = vecA.getMagnitude();

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}

TEST(MathVector3, Normalize)
{
    Ocular::Math::Vector3d vecA(10.0, 10.0, 0.0);
    Ocular::Math::Vector3d expected(0.7071, 0.7071, 0.0);
   
    vecA.normalize();
    
    EXPECT_TRUE((vecA == expected));
}

TEST(MathVector3, CrossProduct)
{
    Ocular::Math::Vector3d vecA(10.0, 10.0, 0.0);
    Ocular::Math::Vector3d vecB(33.0, 10.8, 3.0);
    
    Ocular::Math::Vector3d expected(30.0, -30.0, -222.0);
    Ocular::Math::Vector3d result = vecA.cross(vecB);
    
    EXPECT_TRUE((expected == result));
}

TEST(MathVector3, DotProduct)
{
    Ocular::Math::Vector3d vecA(10.0, 10.0, 0.0);
    Ocular::Math::Vector3d vecB(33.0, 10.8, 3.0);

    double expected = 438.0;
    double result = vecA.dot(vecB);

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}

TEST(MathVector3, AngleBetween)
{
    Ocular::Math::Vector3d vecA(10.0, 10.0, 0.0);
    Ocular::Math::Vector3d vecB(33.0, 10.8, 3.0);

    double expected = 0.476383;
    double result = vecA.angleBetween(vecB);

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}

TEST(MathVector3, Distance)
{
    Ocular::Math::Vector3d vecA(10.0, 10.0, 0.0);
    Ocular::Math::Vector3d vecB(33.0, 10.8, 3.0);

    double expected = 23.2086;
    double result = vecA.distanceTo(vecB);

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}

TEST(MathVector3, Midpoint)
{
    Ocular::Math::Vector3d vecA(10.0, 10.0, 0.0);
    Ocular::Math::Vector3d vecB(33.0, 10.8, 3.0);

    Ocular::Math::Vector3d expected = Ocular::Math::Vector3d(21.5, 10.4, 1.5);
    Ocular::Math::Vector3d result = Ocular::Math::Vector3d::midpoint(vecA, vecB);
    
    EXPECT_TRUE((expected == result));
}

TEST(MathVector3, Lerp)
{
    Ocular::Math::Vector3d vecA(10.0, 10.0, 0.0);
    Ocular::Math::Vector3d vecB(33.0, 10.8, 3.0);
    Ocular::Math::Vector3d midpoint = Ocular::Math::Vector3d::midpoint(vecA, vecB);

    Ocular::Math::Vector3d resultZero = Ocular::Math::Vector3d::lerp(vecA, vecB, 0.0);
    Ocular::Math::Vector3d resultHalf = Ocular::Math::Vector3d::lerp(vecA, vecB, 0.5);
    Ocular::Math::Vector3d resultOne  = Ocular::Math::Vector3d::lerp(vecA, vecB, 1.0);

    EXPECT_TRUE((vecA == resultZero));
    EXPECT_TRUE((midpoint == resultHalf));
    EXPECT_TRUE((vecB == resultOne));
}