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

TEST(Conversions, EulerQuaternion)
{
    //  Euler Angles -> Quaternion
    //    Quaternion -> Euler Angles

    Ocular::Math::Euler      euler(90.0f, 45.0f, 180.0f);
    Ocular::Math::Quaternion quaternion = euler.toQuaternion();
    Ocular::Math::Euler      eulerConv = quaternion.toEuler();
    
    /*EXPECT_NEAR(quaternion.w,  0.270598f,  Ocular::Math::EPSILON_FLOAT);
    EXPECT_NEAR(quaternion.x,  0.270598f,  Ocular::Math::EPSILON_FLOAT);
    EXPECT_NEAR(quaternion.y, -0.6532815f, Ocular::Math::EPSILON_FLOAT);
    EXPECT_NEAR(quaternion.z,  0.6532815f, Ocular::Math::EPSILON_FLOAT);*/
    
    EXPECT_NEAR(euler.getYaw(),   eulerConv.getYaw(), Ocular::Math::EPSILON_FLOAT);
    EXPECT_NEAR(euler.getPitch(), eulerConv.getPitch(), Ocular::Math::EPSILON_FLOAT);
    EXPECT_NEAR(euler.getRoll(),  eulerConv.getRoll(), Ocular::Math::EPSILON_FLOAT);
}

TEST(Conversions, EulerMatrix)
{
    //     Euler Angles -> Rotation Matrix
    //  Rotation Matrix -> Euler Angles

    Ocular::Math::Euler      euler(90.0f, 45.0f, 180.0f);
    Ocular::Math::Matrix3x3f matrix = euler.toRotationMatrix();
    Ocular::Math::Euler      eulerConv = matrix.toEuler();

    // ...
    
    EXPECT_NEAR(euler.getYaw(),   eulerConv.getYaw(), Ocular::Math::EPSILON_FLOAT);
    EXPECT_NEAR(euler.getPitch(), eulerConv.getPitch(), Ocular::Math::EPSILON_FLOAT);
    EXPECT_NEAR(euler.getRoll(),  eulerConv.getRoll(), Ocular::Math::EPSILON_FLOAT);
}

TEST(Conversions, QuaternionMatrix)
{
    //       Quaternion -> Rotation Matrix
    //  Rotation Matrix -> Quaternion

    Ocular::Math::Quaternion quat(1.0f, 0.0f, 0.0f, 0.0f);
    Ocular::Math::Matrix3x3f matrix = quat.toRotationMatrix();
    Ocular::Math::Quaternion quatConv = matrix.toQuaternion();

    // ...
    
    EXPECT_NEAR(quat.w, quatConv.w, Ocular::Math::EPSILON_FLOAT);
    EXPECT_NEAR(quat.x, quatConv.x, Ocular::Math::EPSILON_FLOAT);
    EXPECT_NEAR(quat.y, quatConv.y, Ocular::Math::EPSILON_FLOAT);
    EXPECT_NEAR(quat.z, quatConv.z, Ocular::Math::EPSILON_FLOAT);
}

TEST(Conversions, EulerQuaternionMatrix)
{
    //  Euler Angles -> Rotation Matrix -> Quaternion -> Euler Angles -> Quaternion -> Rotation Matrix -> Euler Angles

    Ocular::Math::Euler start(90.0f, 90.0f, 90.0f);
    Ocular::Math::Euler end = start.toRotationMatrix().toQuaternion().toEuler().toQuaternion().toRotationMatrix().toEuler();
    
    EXPECT_NEAR(start.getYaw(),   end.getYaw(),   Ocular::Math::EPSILON_DOUBLE);
    EXPECT_NEAR(start.getPitch(), end.getPitch(), Ocular::Math::EPSILON_DOUBLE);
    EXPECT_NEAR(start.getRoll(),  end.getRoll(),  Ocular::Math::EPSILON_DOUBLE);
}

