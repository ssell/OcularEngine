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

#include "gtest/gtest.h"
#include "Texture/RandomTexture2D.hpp"
#include "Texture/TextureSavers/TextureResourceSaver_PNG.hpp"
#include "OcularEngine.hpp"

using namespace Ocular::Math::Random;

//------------------------------------------------------------------------------------------

static const int64_t SEED = 1337;
static const bool RUN_PRNG_TESTS = false;
static const Ocular::Graphics::TextureResourceSaver_PNG pngSaver;

//------------------------------------------------------------------------------------------

TEST(PRNG, MersenneTwister19937)
{
    if(RUN_PRNG_TESTS)
    {
        auto prng = CreatePRNG(PRNGImplementation::MersenneTwister, SEED);
        Ocular::Graphics::RandomTexture2D* texture = new Ocular::Graphics::RandomTexture2D(prng, 800, 600);

        EXPECT_TRUE(OcularEngine.ResourceManager()->saveResource(texture, Ocular::Core::File("TestOutput/MersenneTwisterTest.png")));

        delete texture;
        texture = nullptr;
    }
}

TEST(PRNG, MersenneTwister127)
{
    if(RUN_PRNG_TESTS)
    {
        auto prng = CreatePRNG(PRNGImplementation::TinyMersenneTwister, SEED);
        Ocular::Graphics::RandomTexture2D* texture = new Ocular::Graphics::RandomTexture2D(prng, 800, 600);

        EXPECT_TRUE(OcularEngine.ResourceManager()->saveResource(texture, Ocular::Core::File("TestOutput/TinyMersenneTwisterTest.png")));

        delete texture;
        texture = nullptr;
    }
}

TEST(PRNG, CMWC131104)
{
    if(RUN_PRNG_TESTS)
    {
        auto prng = CreatePRNG(PRNGImplementation::CMWC, SEED);
        Ocular::Graphics::RandomTexture2D* texture = new Ocular::Graphics::RandomTexture2D(prng, 800, 600);

        EXPECT_TRUE(OcularEngine.ResourceManager()->saveResource(texture, Ocular::Core::File("TestOutput/CMWCTest.png")));

        delete texture;
        texture = nullptr;
    }
}

TEST(PRNG, WELL512)
{
    if(RUN_PRNG_TESTS)
    {
        auto prng = CreatePRNG(PRNGImplementation::WELL, SEED);
        Ocular::Graphics::RandomTexture2D* texture = new Ocular::Graphics::RandomTexture2D(prng, 800, 600);

        EXPECT_TRUE(OcularEngine.ResourceManager()->saveResource(texture, Ocular::Core::File("TestOutput/WELLTest.png")));

        delete texture;
        texture = nullptr;
    }
}

TEST(PRNG, XorShift96)
{
    if(RUN_PRNG_TESTS)
    {
        auto prng = CreatePRNG(PRNGImplementation::XorShift, SEED);
        Ocular::Graphics::RandomTexture2D* texture = new Ocular::Graphics::RandomTexture2D(prng, 800, 600);

        EXPECT_TRUE(OcularEngine.ResourceManager()->saveResource(texture, Ocular::Core::File("TestOutput/XorShiftTest.png")));

        delete texture;
        texture = nullptr;
    }
}