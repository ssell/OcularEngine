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

#include "Math/Matrix4x4.hpp"
#include "gtest/gtest.h"

//------------------------------------------------------------------------------------------

const Ocular::Math::Matrix4x4d matA( 1.0,  2.0,  3.0,  0.0, 
                                     4.0,  5.0,  6.0,  0.0, 
                                     7.0,  8.0,  9.0,  0.0,
                                    10.0, 11.0, 12.0,  1.0);

const Ocular::Math::Matrix4x4d matB(12.0, 11.0, 10.0,  0.0, 
                                     9.0,  8.0,  7.0,  0.0, 
                                     6.0,  5.0,  4.0,  0.0,
                                     3.0,  2.0,  1.0,  1.0);

TEST(Matrix4x4, Addition)
{
    const Ocular::Math::Matrix4x4d result = matA + matB;
    const Ocular::Math::Matrix4x4d expected(13.0, 13.0, 13.0, 0.0,
                                            13.0, 13.0, 13.0, 0.0,
                                            13.0, 13.0, 13.0, 0.0,
                                            13.0, 13.0, 13.0, 2.0);

    EXPECT_TRUE((result == expected));
}

TEST(Matrix4x4, Subtraction)
{
    const Ocular::Math::Matrix4x4d result = matA - matB;
    const Ocular::Math::Matrix4x4d expected(-11.0, -9.0, -7.0, 0.0,
                                             -5.0, -3.0, -1.0, 0.0,
                                              1.0,  3.0,  5.0, 0.0,
                                              7.0,  9.0, 11.0, 0.0);

    EXPECT_TRUE((result == expected));
}

TEST(Matrix4x4, MatrixMultiplication)
{
    const Ocular::Math::Matrix4x4d result = matA * matB;
    const Ocular::Math::Matrix4x4d expected( 48.0,  42.0,  36.0,  0.0,
                                            129.0, 114.0,  99.0,  0.0,
                                            210.0, 186.0, 162.0,  0.0,
                                            294.0, 260.0, 226.0,  1.0);

    EXPECT_TRUE((result == expected));
}

TEST(Matrix4x4, ScalarMultiplication)
{
    const Ocular::Math::Matrix4x4d result = matA * 2.0;
    const Ocular::Math::Matrix4x4d expected( 2.0,  4.0,  6.0,  0.0, 
                                             8.0, 10.0, 12.0,  0.0, 
                                            14.0, 16.0, 18.0,  0.0,
                                            20.0, 22.0, 24.0,  2.0);

    EXPECT_TRUE((result == expected));
}

TEST(Matrix4x4, XRotation)
{
    //------------------------------------------------
    // Test the getter

    const Ocular::Math::Vector3d expected(1.0, 2.0, 3.0);
    Ocular::Math::Vector3d result = matA.getXRotation();

    EXPECT_TRUE((result == expected));

    //------------------------------------------------
    // Test the setter

    const Ocular::Math::Vector3d modified(5.0, 6.0, 5.0);
    Ocular::Math::Matrix4x4d matC = matA;
    
    matC.setXRotation(modified);
    result = matC.getXRotation();

    EXPECT_TRUE((result == modified));
}

TEST(Matrix4x4, YRotation)
{
    //------------------------------------------------
    // Test the getter

    const Ocular::Math::Vector3d expected(4.0, 5.0, 6.0);
    Ocular::Math::Vector3d result = matA.getYRotation();

    EXPECT_TRUE((result == expected));

    //------------------------------------------------
    // Test the setter

    const Ocular::Math::Vector3d modified(5.0, 6.0, 5.0);
    Ocular::Math::Matrix4x4d matC = matA;

    matC.setYRotation(modified);
    result = matC.getYRotation();

    EXPECT_TRUE((result == modified));
}

TEST(Matrix4x4, ZRotation)
{
    //------------------------------------------------
    // Test the getter

    const Ocular::Math::Vector3d expected(7.0, 8.0, 9.0);
    Ocular::Math::Vector3d result = matA.getZRotation();

    EXPECT_TRUE((result == expected));

    //------------------------------------------------
    // Test the setter

    const Ocular::Math::Vector3d modified(5.0, 6.0, 5.0);
    Ocular::Math::Matrix4x4d matC = matA;

    matC.setZRotation(modified);
    result = matC.getZRotation();

    EXPECT_TRUE((result == modified));
}

TEST(Matrix4x4, Position)
{
    //------------------------------------------------
    // Test the getter

    const Ocular::Math::Vector3d expected(10.0, 11.0, 12.0);
    Ocular::Math::Vector3d result = matA.getPosition();

    EXPECT_TRUE((result == expected));

    //------------------------------------------------
    // Test the setter

    const Ocular::Math::Vector3d modified(5.0, 6.0, 5.0);
    Ocular::Math::Matrix4x4d matC = matA;

    matC.setPosition(modified);
    result = matC.getPosition();

    EXPECT_TRUE((result == modified));
}

TEST(Matrix4x4, ElementRowCol)
{
    //------------------------------------------------
    // Test the getter

    const double expected = 8.0;
    double result = matA[2][1];

    EXPECT_NEAR(result, expected, Ocular::Math::EPSILON_DOUBLE);

    //------------------------------------------------
    // Test the setter

    const double modified = 5.0;
    Ocular::Math::Matrix4x4d matC = matA;

    matC[2][1] = modified;
    result = matC[2][1];

    EXPECT_NEAR(result, modified, Ocular::Math::EPSILON_DOUBLE);
}

TEST(Matrix4x4, ElementIndex)
{
    //------------------------------------------------
    // Test the getter

    const double expected = 8.0;
    double result = matA.getElement(9);

    EXPECT_NEAR(result, expected, Ocular::Math::EPSILON_DOUBLE);

    //------------------------------------------------
    // Test the setter

    const double modified = 5.0;
    Ocular::Math::Matrix4x4d matC = matA;

    matC.setElement(9, modified);
    result = matC.getElement(9);

    EXPECT_NEAR(result, modified, Ocular::Math::EPSILON_DOUBLE);
}

TEST(Matrix4x4, Orthographic)
{
    // TODO
}

TEST(Matrix4x4, Perspective)
{
    // TODO
}

TEST(Matrix4x4, Transpose)
{
    const Ocular::Math::Matrix4x4d result = matA.getTranspose();
    const Ocular::Math::Matrix4x4d expected(1.0,  4.0,  7.0, 10.0,
                                            2.0,  5.0,  8.0, 11.0,
                                            3.0,  6.0,  9.0, 12.0,
                                            0.0,  0.0,  0.0,  1.0);

    EXPECT_TRUE(expected == result);
}

TEST(Matrix4x4, Inverse)
{
    const Ocular::Math::Matrix4x4d matrix(  1.0,   6.0,   3.0,   4.0,
                                           10.0,  20.0,  30.0,  55.0,
                                          100.0,  70.0, 300.0, 400.0,
                                            4.0,   3.0,   2.0,   1.0);

    const Ocular::Math::Matrix4x4d expected(-0.225157,  0.033333, -0.003082,  0.300000,
                                             0.188679,  0.000000, -0.001887,  0.000000,
                                             0.249057, -0.100000,  0.011509, -0.100000,
                                            -0.163522,  0.066667, -0.005031,  0.000000);

    Ocular::Math::Matrix4x4d result;
    
    try
    {
        result = matrix.getInverse();
    }
    catch(Ocular::Core::Exception e)
    {
        FAIL();
    }

    EXPECT_TRUE(expected == result);
}