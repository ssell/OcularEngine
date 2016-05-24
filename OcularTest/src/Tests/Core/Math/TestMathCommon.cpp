/**
 * Copyright 2014-2016 Steven T Sell (ssell@vertexfragment.com)
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

#ifdef _DEBUG

#include "gtest/gtest.h"

#include <boost/utility/binary.hpp>

//------------------------------------------------------------------------------------------

TEST(MathCommon, Normalise)
{
    double dValue = 240.0f;
    dValue = Ocular::Math::Normalize<double>(dValue, 0.0, 180.0);

    EXPECT_NEAR(dValue, 60.0, Ocular::Math::EPSILON_DOUBLE);

    int iValue = -20;
    iValue = Ocular::Math::Normalize<int>(iValue, -18, 18);

    EXPECT_EQ(iValue, 16);
}

TEST(MathCommon, DegreesToRadians)
{
    double degrees = 180.0;
    double result  = Ocular::Math::DegreesToRadians<double>(degrees);

    EXPECT_NEAR(result, Ocular::Math::PI, Ocular::Math::EPSILON_DOUBLE);

    degrees = -90.0;
    result  = Ocular::Math::DegreesToRadians<double>(degrees);

    EXPECT_NEAR(result, -Ocular::Math::PI_OVER_TWO, Ocular::Math::EPSILON_DOUBLE);

    degrees = 0.0;
    result  = Ocular::Math::DegreesToRadians<double>(degrees);

    EXPECT_NEAR(result, 0.0, Ocular::Math::EPSILON_DOUBLE);
}

TEST(MathCommon, RadiansToDegrees)
{
    double radians = Ocular::Math::PI;
    double result  = Ocular::Math::RadiansToDegrees<double>(radians);

    EXPECT_NEAR(result, 180.0, Ocular::Math::EPSILON_DOUBLE);

    radians = -Ocular::Math::PI_OVER_TWO;
    result  = Ocular::Math::RadiansToDegrees<double>(radians);

    EXPECT_NEAR(result, -90.0, Ocular::Math::EPSILON_DOUBLE);

    radians = 0.0;
    result  = Ocular::Math::RadiansToDegrees<double>(radians);

    EXPECT_NEAR(result, 0.0, Ocular::Math::EPSILON_DOUBLE);
}

TEST(MathCommon, Clamp)
{
    double valA = 35.0;

    double expectA = 20.0;
    double expectB = 50.0;
    double expectC = 35.0;

    double resultA = Ocular::Math::Clamp<double>(valA, 0.0, 20.0);
    double resultB = Ocular::Math::Clamp<double>(valA, 50.0, 100.0);
    double resultC = Ocular::Math::Clamp<double>(valA, 0.0, 100.0);

    EXPECT_NEAR(expectA, resultA, Ocular::Math::EPSILON_DOUBLE);
    EXPECT_NEAR(expectB, resultB, Ocular::Math::EPSILON_DOUBLE);
    EXPECT_NEAR(expectC, resultC, Ocular::Math::EPSILON_DOUBLE);
}

TEST(MathCommon, RoundUpDecimal)
{
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
    double valA = 1250.0;
    double valB = 18.0;

    double expectA = 1300.0;
    double expectB = 100.0;

    double resultA = Ocular::Math::RoundUpPowTen<double>(valA, 2);
    double resultB = Ocular::Math::RoundUpPowTen<double>(valB, 2);

    EXPECT_NEAR(expectA, resultA, Ocular::Math::EPSILON_DOUBLE);
    EXPECT_NEAR(expectB, resultB, Ocular::Math::EPSILON_DOUBLE);
}

TEST(MathCommon, RoundDownDecimal)
{
    double valA = 0.2749999;
    double valB = 0.975;
    double valC = 0.86736;

    double expectA = 0.274;
    double expectB = 0.97;
    double expectC = 0.867;

    double resultA = Ocular::Math::RoundDownDecimal<double>(valA, 3);
    double resultB = Ocular::Math::RoundDownDecimal<double>(valB, 2);
    double resultC = Ocular::Math::RoundDownDecimal<double>(valC, 3);

    EXPECT_NEAR(expectA, resultA, Ocular::Math::EPSILON_DOUBLE);
    EXPECT_NEAR(expectB, resultB, Ocular::Math::EPSILON_DOUBLE);
    EXPECT_NEAR(expectC, resultC, Ocular::Math::EPSILON_DOUBLE);
}

TEST(MathCommon, RoundDownPowTen)
{
    double valA = 1250.0;
    double valB = 18.0;

    double expectA = 1200.0;
    double expectB = 0.0;

    double resultA = Ocular::Math::RoundDownPowTen<double>(valA, 2);
    double resultB = Ocular::Math::RoundDownPowTen<double>(valB, 2);

    EXPECT_NEAR(expectA, resultA, Ocular::Math::EPSILON_DOUBLE);
    EXPECT_NEAR(expectB, resultB, Ocular::Math::EPSILON_DOUBLE);
}

TEST(MathCommon, RoundDecimal)
{
    double valA = 0.127;
    double valB = 0.123;

    double expectA = 0.13;
    double expectB = 0.12;

    double resultA = Ocular::Math::RoundDecimal(valA, 2);
    double resultB = Ocular::Math::RoundDecimal(valB, 2);

    EXPECT_NEAR(expectA, resultA, Ocular::Math::EPSILON_DOUBLE);
    EXPECT_NEAR(expectB, resultB, Ocular::Math::EPSILON_DOUBLE);
}

TEST(MathCommon, RoundPowTen)
{
    double valA = 1270.0;
    double valB = 1230.0;

    double expectA = 1300.0;
    double expectB = 1200.0;

    double resultA = Ocular::Math::RoundPowTen<double>(valA, 2);
    double resultB = Ocular::Math::RoundPowTen<double>(valB, 2);

    EXPECT_NEAR(expectA, resultA, Ocular::Math::EPSILON_DOUBLE);
    EXPECT_NEAR(expectB, resultB, Ocular::Math::EPSILON_DOUBLE);
}

TEST(MathCommon, Clz32)
{
	const uint32_t valueA    = 100;
	const uint32_t expectedA = 25;
	const uint32_t resultA   = Ocular::Math::Clz(valueA);

	EXPECT_EQ(expectedA, resultA);

	const uint32_t valueB    = 4294967295;
	const uint32_t expectedB = 0;
	const uint32_t resultB   = Ocular::Math::Clz(valueB);

	EXPECT_EQ(expectedB, resultB);

	const uint32_t valueC    = 1;
	const uint32_t expectedC = 31;
	const uint32_t resultC   = Ocular::Math::Clz(valueC);

	EXPECT_EQ(expectedC, resultC);
}

TEST(MathCommon, Clz64)
{
	const uint64_t valueA    = 100;
	const uint64_t expectedA = 57;
	const uint64_t resultA   = Ocular::Math::Clz(valueA);

	EXPECT_EQ(expectedA, resultA);

	const uint64_t valueB    = 4294967295;
	const uint64_t expectedB = 32;
	const uint64_t resultB   = Ocular::Math::Clz(valueB);

	EXPECT_EQ(expectedB, resultB);

	const uint64_t valueC    = 1;
	const uint64_t expectedC = 63;
	const uint64_t resultC   = Ocular::Math::Clz(valueC);

	EXPECT_EQ(expectedC, resultC);
}

#endif