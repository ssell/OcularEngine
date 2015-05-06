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
#include "Math/Noise/PerlinNoise.hpp"
#include "Math/Noise/SimplexNoise.hpp"
#include "Math/Noise/WaveletNoise.hpp"
#include "OcularEngine.hpp"

using namespace Ocular::Math::Noise;

//------------------------------------------------------------------------------------------

static const bool RUN_NOISE_TESTS = true;
static const Ocular::Graphics::TextureResourceSaver_PNG pngSaver;

//------------------------------------------------------------------------------------------

TEST(Noise, Perlin)
{
    if(false)
    {
        std::shared_ptr<PerlinNoise> noise = std::make_shared<PerlinNoise>();

        noise->setOctaves(1);
        noise->setPersistence(1.0f);
        noise->setScale(0.1f);

        Ocular::Graphics::NoiseTexture2D* texture = new Ocular::Graphics::NoiseTexture2D(noise, 800, 600);

        EXPECT_TRUE(OcularEngine.ResourceManager()->saveResource(texture, Ocular::Core::File("TestOutput/PerlinNoise.png")));

        delete texture;
        texture = nullptr;
    }
}

TEST(Noise, Simplex)
{
    if(RUN_NOISE_TESTS)
    {
        std::shared_ptr<SimplexNoise> noise = std::make_shared<SimplexNoise>();
        Ocular::Graphics::NoiseTexture2D* texture = new Ocular::Graphics::NoiseTexture2D(noise, 800, 600);

        EXPECT_TRUE(OcularEngine.ResourceManager()->saveResource(texture, Ocular::Core::File("TestOutput/SimplexNoise.png")));

        delete texture;
        texture = nullptr;
    }
}

TEST(Noise, )
{
    if(RUN_NOISE_TESTS)
    {
        std::shared_ptr<WaveletNoise> noise = std::make_shared<WaveletNoise>();
        Ocular::Graphics::NoiseTexture2D* texture = new Ocular::Graphics::NoiseTexture2D(noise, 800, 600);

        EXPECT_TRUE(OcularEngine.ResourceManager()->saveResource(texture, Ocular::Core::File("TestOutput/WaveletNoise.png")));

        delete texture;
        texture = nullptr;
    }
}