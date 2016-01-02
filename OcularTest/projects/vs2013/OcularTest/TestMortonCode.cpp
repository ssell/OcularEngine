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

#include "Math/MortonCode.hpp"
#include "Math/Vector3.hpp"

#include "gtest/gtest.h"

using namespace Ocular::Math;

//------------------------------------------------------------------------------------------

TEST(MortonCode, Proximity)
{
    // Tests to ensure that the morton codes are ordering via proximity.

    const Vector3f pointA(0.0f, 0.0f, 0.0f);
    const Vector3f pointB(0.1f, 0.0f, 0.0f);
    const Vector3f pointC(0.0f, 0.2f, 0.0f);
    const Vector3f pointD(0.1f, 0.2f, 0.0f);
    const Vector3f pointE(0.7f, 0.5f, 0.7f);
    const Vector3f pointF(0.7001f, 0.5f, 0.7f);
    const Vector3f pointG(0.9f, 0.9f, 0.9f);
    
    const uint64_t mortonA = MortonCode::calculate(pointA.x, pointA.y, pointA.z);
    const uint64_t mortonB = MortonCode::calculate(pointB.x, pointB.y, pointB.z);
    const uint64_t mortonC = MortonCode::calculate(pointC.x, pointC.y, pointC.z);
    const uint64_t mortonD = MortonCode::calculate(pointD.x, pointD.y, pointD.z);
    const uint64_t mortonE = MortonCode::calculate(pointE.x, pointE.y, pointE.z);
    const uint64_t mortonF = MortonCode::calculate(pointF.x, pointF.y, pointF.z);
    const uint64_t mortonG = MortonCode::calculate(pointG.x, pointG.y, pointG.z);
    
    EXPECT_TRUE(mortonA < mortonB);
    EXPECT_TRUE(mortonB < mortonC);
    EXPECT_TRUE(mortonC < mortonD);
    EXPECT_TRUE(mortonD < mortonE);
    EXPECT_TRUE(mortonE < mortonF);
    EXPECT_TRUE(mortonF < mortonG);
}