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

#include "Math/Noise/PerlinNoise.hpp"
#include "Math/MathCommon.hpp"
#include "Math/Random/Random.hpp"
#include "Math/Vector2.hpp"

//------------------------------------------------------------------------------------------

static float sigmoidCurve(const float t)
{
    return (t * t * (3.0f - 2.0f * t));
}

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        namespace Noise
        {
            //------------------------------------------------------------------------------
            // CONSTRUCTORS
            //------------------------------------------------------------------------------

            PerlinNoise::PerlinNoise()
                : ANoise(),
                  m_Octaves(6),
                  m_Persistence(0.5f),
                  m_Scale(0.01f),
                  m_Seed(0)
            {
                m_PRNG = Random::CreatePRNG(Random::MersenneTwister);
            }

            PerlinNoise::~PerlinNoise()
            {
            
            }

            //------------------------------------------------------------------------------
            // PUBLIC METHODS
            //------------------------------------------------------------------------------

            float PerlinNoise::getValue(float const x)
            {
                float result = 0.0f;

                return result;
            }

            float PerlinNoise::getValue(float const x, float const y)
            {
                float result       = 0.0f;
                float frequency    = m_Scale;
                float amplitude    = 1.0f;
                float maxAmplitude = 0.0f;

                for(uint32_t i = 0; i < m_Octaves; i++)
                {
                    result += getInterpolatedNoise((x * frequency), (y * frequency)) * amplitude;
                    
                    frequency *= 2.0f;
                    maxAmplitude += amplitude;
                    amplitude *= m_Persistence;
                }

                result /= maxAmplitude;

                return result;
            }

            float PerlinNoise::getValue(float const x, float const y, float const z)
            {
                float result = 0.0f;

                return result;
            }

            void PerlinNoise::setOctaves(uint32_t octaves)
            {
                m_Octaves = octaves;
            }

            void PerlinNoise::setPersistence(float persistence)
            {
                m_Persistence = persistence;
            }

            void PerlinNoise::setScale(float scale)
            {
                m_Scale = scale;
            }

            //------------------------------------------------------------------------------
            // PROTECTED METHODS
            //------------------------------------------------------------------------------

            void PerlinNoise::seed(int64_t seed)
            {
                m_Seed = seed;
            }

            float PerlinNoise::getInterpolatedNoise(float const x)
            {
                return 0.0f;
            }

            float PerlinNoise::getInterpolatedNoise(float const x, float const y)
            {
                float intX  = static_cast<float>(static_cast<int>(x));
                float intY  = static_cast<float>(static_cast<int>(y));
                float fracX = x - intX;
                float fracY = y - intY;

                float value0 = getSmoothNoise(intX, intY);
                float value1 = getSmoothNoise(intX + 1.0f, intY);
                float value2 = getSmoothNoise(intX, intY + 1.0f);
                float value3 = getSmoothNoise(intX + 1.0f, intY + 1.0f);

                float interpolated0 = InterpolateCosine(value0, value1, fracX);
                float interpolated1 = InterpolateCosine(value2, value3, fracX);

                return InterpolateCosine(interpolated0, interpolated1, fracY);
            }

            float PerlinNoise::getInterpolatedNoise(float const x, float const y, float const z)
            {
                return 0.0f;
            }

            float PerlinNoise::getSmoothNoise(float const x, float const y)
            {
                float corners = (getRandom((x - 1.0f), (y - 1.0f)) + getRandom((x + 1.0f), (y - 1.0f)) + getRandom((x - 1.0f), (y + 1.0f)) + getRandom((x + 1.0f), (y + 1.0f))) / 16.0f;
                float sides   = (getRandom((x - 1.0f), y) + getRandom((x + 1.0f), y) + getRandom(x, (y - 1.0f)) + getRandom(x, (y + 1.0f))) / 8.0f;
                float center  = getRandom(x, y) / 4.0f;

                float result = corners + sides + center;

                return result;
            }

            float PerlinNoise::getRandom(float const x, float const y)
            {
                int32_t n = static_cast<int32_t>(x) + static_cast<int32_t>(y) * 57;
                n = (n << 13) ^ n;

                return (1.0f - static_cast<float>(((n * (n * n * 15731 + 789221) + 1376312589) & 2147483647)) / 1073741824.0f);
            }

            //------------------------------------------------------------------------------
            // PRIVATE METHODS
            //------------------------------------------------------------------------------
        }
    }
}