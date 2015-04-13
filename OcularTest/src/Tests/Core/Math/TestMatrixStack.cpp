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

#include "Math/MatrixStack.hpp"
#include "gtest/gtest.h"

//------------------------------------------------------------------------------------------

TEST(MatrixStack, Push)
{
    Ocular::Math::MatrixStackd stack;
    Ocular::Math::Matrix4x4d matrix;

    matrix.setPosition(10.0, 100.0, 1000.0);
    stack.push(matrix);

    Ocular::Math::Matrix4x4d result;
    
    EXPECT_TRUE(stack.peek(&result));
    EXPECT_TRUE(matrix == result);
}

TEST(MatrixStack, Pop)
{
    Ocular::Math::MatrixStackd stack;
    Ocular::Math::Matrix4x4d result;

    EXPECT_FALSE(stack.pop(&result));

    stack.loadIdentity();

    EXPECT_TRUE(stack.pop(&result));
}

TEST(MatrixStack, Combine)
{
    Ocular::Math::MatrixStackd stack;
    Ocular::Math::Matrix4x4d matrix;
    Ocular::Math::Matrix4x4d result;

    matrix.setPosition(10.0, 100.0, 1000.0);
    matrix.setXRotation(10.0, 0.0, 0.0);

    stack.loadIdentity();
    stack.combine(matrix);

    EXPECT_TRUE(stack.peek(&result));
    EXPECT_TRUE(matrix == result);
}