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
}

TEST(Conversions, EulerMatrix)
{
    //     Euler Angles -> Rotation Matrix
    //  Rotation Matrix -> Euler Angles
}

TEST(Conversions, QuaternionMatrix)
{
    //       Quaternion -> Rotation Matrix
    //  Rotation Matrix -> Quaternion
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

