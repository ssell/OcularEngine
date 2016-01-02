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

#include "Math/Matrix3x3.hpp"
#include "gtest/gtest.h"

//#include "glm/glm.hpp"
//#include "glm/gtc/quaternion.hpp"

//------------------------------------------------------------------------------------------
/*
TEST(Conversions, EulerQuaternion)
{
    //  Euler Angles -> Quaternion
    //    Quaternion -> Euler Angles

    Ocular::Math::Euler      euler(90.0f, 45.0f, 180.0f);
    Ocular::Math::Quaternion quaternion = euler.toQuaternion();
    Ocular::Math::Euler      eulerConv = quaternion.toEuler();
    
    EXPECT_NEAR(euler.getYaw(),   eulerConv.getYaw(), Ocular::Math::EPSILON_FLOAT);
    EXPECT_NEAR(euler.getPitch(), eulerConv.getPitch(), Ocular::Math::EPSILON_FLOAT);
    EXPECT_NEAR(euler.getRoll(),  eulerConv.getRoll(), Ocular::Math::EPSILON_FLOAT);
}

TEST(Conversions, EulerMatrix)
{
    //     Euler Angles -> Rotation Matrix
    //  Rotation Matrix -> Euler Angles

    Ocular::Math::Euler      euler(90.0f, 45.0f, 180.0f);
    Ocular::Math::Matrix3x3 matrix = euler.toRotationMatrix();
    Ocular::Math::Euler      eulerConv = matrix.toEuler();
    
    EXPECT_NEAR(euler.getYaw(),   eulerConv.getYaw(), Ocular::Math::EPSILON_FLOAT);
    EXPECT_NEAR(euler.getPitch(), eulerConv.getPitch(), Ocular::Math::EPSILON_FLOAT);
    EXPECT_NEAR(euler.getRoll(),  eulerConv.getRoll(), Ocular::Math::EPSILON_FLOAT);
}

TEST(Conversions, QuaternionMatrix)
{
    //       Quaternion -> Rotation Matrix
    //  Rotation Matrix -> Quaternion

    Ocular::Math::Quaternion quat(0.270598114f, -0.65328151f, -0.65328151f, -0.270597935f);
    Ocular::Math::Matrix3x3 matrix(quat);
    Ocular::Math::Quaternion quatConv(matrix);
    
    // The final quaternion is the opposite sign of the original.
    // Is this correct? Other math libraries seem to agree with
    // this (Unreal Engine, GLM, etc.) but I am not sure why
    // this is. Need to look into it more to assure myself that
    // the correct values are being calculated and returned.

    // NOTE: The above is temporarily out-of-date as the conversions
    // are currently just using known working conversions (mainly
    // converting between eulers). This way a seamless chain of
    // conversions can happen (see EulerMatrixQuaternion test).

    EXPECT_NEAR(quat.w, quatConv.w, Ocular::Math::EPSILON_FLOAT);  
    EXPECT_NEAR(quat.x, quatConv.x, Ocular::Math::EPSILON_FLOAT);
    EXPECT_NEAR(quat.y, quatConv.y, Ocular::Math::EPSILON_FLOAT);
    EXPECT_NEAR(quat.z, quatConv.z, Ocular::Math::EPSILON_FLOAT);

    // Sanity check

    float dotProduct = quat.dot(quatConv);
    dotProduct = fabs(dotProduct);

    EXPECT_NEAR(dotProduct, 1.0f, 0.1f);
}

TEST(Conversions, EulerMatrixQuaternion)
{
    Ocular::Math::Euler eulerStart(90.0f, 45.0f, 180.0f);
    Ocular::Math::Euler eulerEnd = eulerStart.toRotationMatrix().toQuaternion().toEuler().toQuaternion().toRotationMatrix().toEuler();
    
    EXPECT_NEAR(eulerStart.getYaw(),   eulerEnd.getYaw(),   Ocular::Math::EPSILON_FLOAT);
    EXPECT_NEAR(eulerStart.getPitch(), eulerEnd.getPitch(), Ocular::Math::EPSILON_FLOAT);
    EXPECT_NEAR(eulerStart.getRoll(),  eulerEnd.getRoll(),  Ocular::Math::EPSILON_FLOAT);
}










/*
TEST(Conversions, GLM_EulerQuaternion)
{
    glm::vec3 euler(0.785398066f, 1.57079613f, 3.14159226f); // GLM does Pitch, Yaw, Roll as opposed to Yaw, Pitch, Roll
    glm::quat quat(euler);
    glm::vec3 eulerConv = glm::eulerAngles(quat);

    // ...

    EXPECT_NEAR(euler.y, eulerConv.y, Ocular::Math::EPSILON_FLOAT);
    EXPECT_NEAR(euler.x, eulerConv.x, Ocular::Math::EPSILON_FLOAT);
    EXPECT_NEAR(euler.z, eulerConv.z, Ocular::Math::EPSILON_FLOAT);
}

TEST(Conversions, GLM_QuaternionMatrix)
{
    glm::quat   quat(0.270598114f, -0.65328151f, -0.65328151f, -0.270597935f);
    glm::mat3x3 matrix(quat);
    glm::quat   quatConv(matrix);

    // ...
    
    EXPECT_NEAR(quat.w, quatConv.w, Ocular::Math::EPSILON_FLOAT);
    EXPECT_NEAR(quat.x, quatConv.x, Ocular::Math::EPSILON_FLOAT);
    EXPECT_NEAR(quat.y, quatConv.y, Ocular::Math::EPSILON_FLOAT);
    EXPECT_NEAR(quat.z, quatConv.z, Ocular::Math::EPSILON_FLOAT);
}
*/