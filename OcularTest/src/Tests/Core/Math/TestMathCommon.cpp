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

#include "Math/MathCommon.hpp"
#include "gtest/gtest.h"

//------------------------------------------------------------------------------------------

TEST(MathCommon, Clamp)
{

}

TEST(MathCommon, RoundUpDecimal)
{
    //------------------------------------------------
    // Test rounding to a given decimal point precision

    double valA = 0.2749999;
    double valB = 0.975;
    double valC = 0.86736;

    double expectA = 0.275;
    double expectB = 0.98;
    double expectC = 0.868;

    double resultA = Ocular::Math::RoundUpDecimal<double>(valA, 3);
    double resultB = Ocular::Math::RoundUpDecimal<double>(valB, 2);
    double resultC = Ocular::Math::RoundUpDecimal<double>(valC, 3);

    EXPECT_NEAR(expectA, resultA, Ocular::Math::EPSILON_DOUBLE);
    EXPECT_NEAR(expectB, resultB, Ocular::Math::EPSILON_DOUBLE);
    EXPECT_NEAR(expectC, resultC, Ocular::Math::EPSILON_DOUBLE);
}

TEST(MathCommon, RoundUpPowTen)
{
    //------------------------------------------------
    // Test rounding to a given integer power of ten precision

    double valD = 1250.0;
    double valE = 18.0;

    double expectD = 1300.0;
    double expectE = 100.0;

    double resultD = Ocular::Math::RoundUpPowTen<double>(valD, 2);
    double resultE = Ocular::Math::RoundUpPowTen<double>(valE, 2);

    EXPECT_NEAR(expectD, resultD, Ocular::Math::EPSILON_DOUBLE);
    EXPECT_NEAR(expectE, resultE, Ocular::Math::EPSILON_DOUBLE);
}