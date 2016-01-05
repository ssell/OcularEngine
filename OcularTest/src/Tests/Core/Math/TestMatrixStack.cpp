/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
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
#include "Math/Vector4.hpp"

#ifdef _DEBUG

#include "gtest/gtest.h"

using namespace Ocular;
using namespace Ocular::Math;

//------------------------------------------------------------------------------------------

TEST(MatrixStack, Push)
{
    MatrixStack stack;
    Matrix4x4 matrix;

    matrix.setCol(2, Vector3f(10.0f, 100.0f, 1000.0f));
    stack.push(matrix);

    Matrix4x4 result;
    
    EXPECT_TRUE(stack.peek(&result));
    EXPECT_TRUE(matrix == result);
}

TEST(MatrixStack, Pop)
{
    MatrixStack stack;
    Matrix4x4 result;

    EXPECT_FALSE(stack.pop(&result));

    stack.loadIdentity();

    EXPECT_TRUE(stack.pop(&result));
}

TEST(MatrixStack, Combine)
{
    MatrixStack stack;
    Matrix4x4 matrix;
    Matrix4x4 result;

    matrix.setCol(2, Vector3f(10.0, 100.0, 1000.0));
    matrix.setCol(0, Vector3f(10.0, 0.0, 0.0));

    stack.loadIdentity();
    stack.combine(matrix);

    EXPECT_TRUE(stack.peek(&result));
    EXPECT_TRUE(matrix == result);
}

#endif