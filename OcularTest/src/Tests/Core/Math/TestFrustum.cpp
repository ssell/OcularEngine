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

#include "Math/Geometry/Frustum.hpp"
#include "gtest/gtest.h"

using namespace Ocular::Math;

//------------------------------------------------------------------------------------------

TEST(Frustum, Test)
{
    Frustum frustum;

    frustum.setView(Vector3f(0.0f, 0.0f, 0.0f), Vector3f::Forward(), Vector3f::Up());
    frustum.setProjection(60.0f, 1024.0f / 768.0f, 1.0f, 100.0f);

    const Vector3f origin = frustum.getOrigin();
    const Vector3f forward = frustum.getForward();
}

TEST(Frustum, Hmmm)
{
    const Matrix4x4f viewMatrix = Matrix4x4f::CreateLookAtMatrix(Vector3f::Identity(), Vector3f::Forward(), Vector3f::Up());
    const Matrix4x4f projMatrix = Matrix4x4f::CreatePerspectiveMatrix(60.0f, (1024.0f / 768.0f), -10.0f, -100.0f);
    const Matrix4x4f viewProjMatrix = viewMatrix * projMatrix;

    Frustum frustum;
    frustum.setViewProjection(viewProjMatrix);

    int a = 0;
    a++;
}