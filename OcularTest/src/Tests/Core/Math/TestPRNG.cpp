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
#include "Texture/NoiseTexture2D.hpp"
#include "Texture/TextureSavers/TextureResourceSaver_PNG.hpp"
#include "Math/Random/BoxMullerSampler.hpp"
#include "OcularEngine.hpp"

using namespace Ocular::Math::Random;

//------------------------------------------------------------------------------------------

static const int64_t SEED = 1337;
static const bool RUN_PRNG_TESTS = true;
static const Ocular::Graphics::TextureResourceSaver_PNG pngSaver;
static const uint32_t TEXTURE_WIDTH = 800;
static const uint32_t TEXTURE_HEIGHT = 600;

//------------------------------------------------------------------------------------------

TEST(PRNG, MersenneTwister19937)
{
    if(RUN_PRNG_TESTS)
    {
        auto prng = CreatePRNG(PRNG::MersenneTwister, SEED);
        Ocular::Graphics::NoiseTexture2D* texture = new Ocular::Graphics::NoiseTexture2D(prng, TEXTURE_WIDTH, TEXTURE_HEIGHT);

        EXPECT_TRUE(OcularEngine.ResourceManager()->saveResource(texture, Ocular::Core::File("TestOutput/MersenneTwisterTest.png")));

        delete texture;
        texture = nullptr;
        prng = nullptr;
    }
}

TEST(PRNG, MersenneTwister127)
{
    if(RUN_PRNG_TESTS)
    {
        auto prng = CreatePRNG(PRNG::TinyMersenneTwister, SEED);
        Ocular::Graphics::NoiseTexture2D* texture = new Ocular::Graphics::NoiseTexture2D(prng, TEXTURE_WIDTH, TEXTURE_HEIGHT);

        EXPECT_TRUE(OcularEngine.ResourceManager()->saveResource(texture, Ocular::Core::File("TestOutput/TinyMersenneTwisterTest.png")));

        delete texture;
        texture = nullptr;
        prng = nullptr;
    }
}

TEST(PRNG, CMWC131104)
{
    if(RUN_PRNG_TESTS)
    {
        auto prng = CreatePRNG(PRNG::CMWC, SEED);
        Ocular::Graphics::NoiseTexture2D* texture = new Ocular::Graphics::NoiseTexture2D(prng, TEXTURE_WIDTH, TEXTURE_HEIGHT);

        EXPECT_TRUE(OcularEngine.ResourceManager()->saveResource(texture, Ocular::Core::File("TestOutput/CMWCTest.png")));

        delete texture;
        texture = nullptr;
        prng = nullptr;
    }
}

TEST(PRNG, WELL512)
{
    if(RUN_PRNG_TESTS)
    {
        auto prng = CreatePRNG(PRNG::WELL, SEED);
        Ocular::Graphics::NoiseTexture2D* texture = new Ocular::Graphics::NoiseTexture2D(prng, TEXTURE_WIDTH, TEXTURE_HEIGHT);

        EXPECT_TRUE(OcularEngine.ResourceManager()->saveResource(texture, Ocular::Core::File("TestOutput/WELLTest.png")));

        delete texture;
        texture = nullptr;
        prng = nullptr;
    }
}

TEST(PRNG, XorShift96)
{
    if(RUN_PRNG_TESTS)
    {
        auto prng = CreatePRNG(PRNG::XorShift, SEED);
        Ocular::Graphics::NoiseTexture2D* texture = new Ocular::Graphics::NoiseTexture2D(prng, TEXTURE_WIDTH, TEXTURE_HEIGHT);

        EXPECT_TRUE(OcularEngine.ResourceManager()->saveResource(texture, Ocular::Core::File("TestOutput/XorShiftTest.png")));

        delete texture;
        texture = nullptr;
        prng = nullptr;
    }
}

TEST(PRNGSampler, BoxMuller)
{
    if(RUN_PRNG_TESTS)
    {
        auto prng = CreatePRNG(PRNG::XorShift, SEED);
        Ocular::Graphics::Texture2D* texture = new Ocular::Graphics::Texture2D(TEXTURE_WIDTH, TEXTURE_HEIGHT);

        BoxMullerSampler sampler(prng);

        for(uint32_t y = 0; y < TEXTURE_HEIGHT; y++)
        {
            for(uint32_t x = 0; x < TEXTURE_WIDTH; x++)
            {
                float value = sampler.next();
                texture->setPixel(x, y, Ocular::Color(value, value, value, 1.0f));
            }
        }

        EXPECT_TRUE(OcularEngine.ResourceManager()->saveResource(texture, Ocular::Core::File("TestOutput/BoxMullerTest.png")));

        delete texture;
        texture = nullptr;
        prng = nullptr;
    }
}