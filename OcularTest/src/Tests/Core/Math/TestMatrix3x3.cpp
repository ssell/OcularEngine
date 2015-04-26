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

#include "Math/Matrix3x3.hpp"
#include "gtest/gtest.h"

//------------------------------------------------------------------------------------------

static const Ocular::Math::Matrix3x3d matA(1.0, 2.0, 3.0,
                                           4.0, 5.0, 6.0,
                                           7.0, 8.0, 9.0);

static const Ocular::Math::Matrix3x3d matB(9.0, 8.0, 7.0,
                                           6.0, 5.0, 4.0,
                                           3.0, 2.0, 1.0);

TEST(Matrix3x3, Addition)
{
    const Ocular::Math::Matrix3x3d result = matA + matB;
    const Ocular::Math::Matrix3x3d expected(10.0, 10.0, 10.0,
                                            10.0, 10.0, 10.0,
                                            10.0, 10.0, 10.0);

    EXPECT_TRUE((result == expected));
}

TEST(Matrix3x3, Subtraction)
{
    const Ocular::Math::Matrix3x3d result = matA - matB;
    const Ocular::Math::Matrix3x3d expected(-8.0, -6.0, -4.0,
                                            -2.0,  0.0,  2.0,
                                             4.0,  6.0,  8.0);

    EXPECT_TRUE((result == expected));
}

TEST(Matrix3x3, MatrixMultiplication)
{
    const Ocular::Math::Matrix3x3d result = matA * matB;
    const Ocular::Math::Matrix3x3d expected( 30.0,  24.0,  18.0,
                                             84.0,  69.0,  54.0,
                                            138.0, 114.0,  90.0);

    EXPECT_TRUE((result == expected));
}

TEST(Matrix3x3, ScalarMultiplication)
{
    const Ocular::Math::Matrix3x3d result = matA * 2.0;
    const Ocular::Math::Matrix3x3d expected (2.0,  4.0,  6.0,
                                             8.0, 10.0, 12.0,
                                            14.0, 16.0, 18.0);

    EXPECT_TRUE((result == expected));
}

TEST(Matrix3x3, XRotation)
{
    //------------------------------------------------
    // Test the getter

    const Ocular::Math::Vector3d expected(1.0, 2.0, 3.0);
    Ocular::Math::Vector3d result = matA.getXRotation();

    EXPECT_TRUE((result == expected));

    //------------------------------------------------
    // Test the setter

    const Ocular::Math::Vector3d modified(5.0, 6.0, 5.0);
    Ocular::Math::Matrix3x3d matC = matA;

    matC.setXRotation(modified);
    result = matC.getXRotation();

    EXPECT_TRUE((result == modified));
}

TEST(Matrix3x3, YRotation)
{
    //------------------------------------------------
    // Test the getter

    const Ocular::Math::Vector3d expected(4.0, 5.0, 6.0);
    Ocular::Math::Vector3d result = matA.getYRotation();

    EXPECT_TRUE((result == expected));

    //------------------------------------------------
    // Test the setter

    const Ocular::Math::Vector3d modified(5.0, 6.0, 5.0);
    Ocular::Math::Matrix3x3d matC = matA;

    matC.setYRotation(modified);
    result = matC.getYRotation();

    EXPECT_TRUE((result == modified));
}

TEST(Matrix3x3, ZRotation)
{
    //------------------------------------------------
    // Test the getter

    const Ocular::Math::Vector3d expected(7.0, 8.0, 9.0);
    Ocular::Math::Vector3d result = matA.getZRotation();

    EXPECT_TRUE((result == expected));

    //------------------------------------------------
    // Test the setter

    const Ocular::Math::Vector3d modified(5.0, 6.0, 5.0);
    Ocular::Math::Matrix3x3d matC = matA;

    matC.setZRotation(modified);
    result = matC.getZRotation();

    EXPECT_TRUE((result == modified));
}

TEST(Matrix3x3, ElementRowCol)
{
    //------------------------------------------------
    // Test the getter

    const double expected = 8.0;
    double result = matA[2][1];

    EXPECT_NEAR(result, expected, Ocular::Math::EPSILON_DOUBLE);

    //------------------------------------------------
    // Test the setter

    const double modified = 5.0;
    Ocular::Math::Matrix3x3d matC = matA;

    matC[2][1] = modified;
    result = matC[2][1];

    EXPECT_NEAR(result, modified, Ocular::Math::EPSILON_DOUBLE);
}

TEST(Matrix3x3, ElementIndex)
{
    //------------------------------------------------
    // Test the getter

    const double expected = 8.0;
    double result = matA.getElement(7);

    EXPECT_NEAR(result, expected, Ocular::Math::EPSILON_DOUBLE);

    //------------------------------------------------
    // Test the setter

    const double modified = 5.0;
    Ocular::Math::Matrix3x3d matC = matA;

    matC.setElement(7, modified);
    result = matC.getElement(7);

    EXPECT_NEAR(result, modified, Ocular::Math::EPSILON_DOUBLE);
}

TEST(Matrix3x3, Transpose)
{
    const Ocular::Math::Matrix3x3d result = Ocular::Math::Matrix3x3d::createTransposeMatrix(matA);
    const Ocular::Math::Matrix3x3d expected(1.0, 4.0, 7.0,
                                            2.0, 5.0, 8.0,
                                            3.0, 6.0, 9.0);
    EXPECT_TRUE(expected == result);
}

TEST(Matrix3x3, Inverse)
{
    // matA is actually a singular matrix, and does not have an inverse.
    // Currently the math library (aka me) doesn't know what to do when 
    // asked to invert a singular matrix, so using a new matrix for this test.

    const Ocular::Math::Matrix3x3d matrix(1.0, 2.0, 3.0,
                                          4.0, 15.0, 6.0,
                                          7.0, 8.0, 9.0);

    const Ocular::Math::Matrix3x3d expected(-0.724999, -0.050000,  0.275000,
                                            -0.050000,  0.100000, -0.050000,
                                             0.608333, -0.050000, -0.058333);


    Ocular::Math::Matrix3x3d result;
    Ocular::Math::Matrix3x3d::createInverseMatrix(matrix, result);

    EXPECT_TRUE(expected == result);
}