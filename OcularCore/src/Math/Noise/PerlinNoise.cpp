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

#include "Math/Noise/PerlinNoise.hpp"
#include "Math/MathCommon.hpp"
#include "Math/Random/Random.hpp"

static const uint32_t B  = 256;
static const uint32_t BM = 255;
static const uint32_t B2 = 512;
static const uint32_t N  = 4096;
static const uint32_t NP = 12;
static const uint32_t NM = 4095;

static const float ONE_OVER_B = 0.00390625f;

//------------------------------------------------------------------------------------------

static void normalize2(float v[2])
{
    float s;

	s = sqrt(v[0] * v[0] + v[1] * v[1]);
	v[0] = v[0] / s;
	v[1] = v[1] / s;
}

static void normalize3(float v[3])
{
    float s;

	s = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] = v[0] / s;
	v[1] = v[1] / s;
	v[2] = v[2] / s;
}

static float sCurve(const float t)
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
                : ANoise()
            {
                m_Octaves = 6;
                m_Persistence = 0.5f;
                m_Scale = 0.01f;

                populate();
            }

            PerlinNoise::~PerlinNoise()
            {
            
            }

            //------------------------------------------------------------------------------
            // PUBLIC METHODS
            //------------------------------------------------------------------------------

            float PerlinNoise::getValue(float const x)
            {
                float result       = 0.0f;
                float frequency    = m_Scale;
                float amplitude    = 1.0f;
                float maxAmplitude = 0.0f;

                for(uint32_t i = 0; i < m_Octaves; i++)
                {
                    result += getRawNoise((x * frequency)) * amplitude;
                    
                    frequency *= 2.0f;
                    maxAmplitude += amplitude;
                    amplitude *= m_Persistence;
                }

                return ((result / maxAmplitude) + 1.0f) * 0.5f;
            }

            float PerlinNoise::getValue(float const x, float const y)
            {
                float result       = 0.0f;
                float frequency    = m_Scale;
                float amplitude    = 1.0f;
                float maxAmplitude = 0.0f;

                for(uint32_t i = 0; i < m_Octaves; i++)
                {
                    result += getRawNoise((x * frequency), (y * frequency)) * amplitude;
                    
                    frequency *= 2.0f;
                    maxAmplitude += amplitude;
                    amplitude *= m_Persistence;
                }

                return (result / maxAmplitude);
            }

            float PerlinNoise::getValue(float const x, float const y, float const z)
            {
                float result       = 0.0f;
                float frequency    = m_Scale;
                float amplitude    = 1.0f;
                float maxAmplitude = 0.0f;

                for(uint32_t i = 0; i < m_Octaves; i++)
                {
                    result += getRawNoise((x * frequency), (y * frequency), (z * frequency)) * amplitude;
                    
                    frequency *= 2.0f;
                    maxAmplitude += amplitude;
                    amplitude *= m_Persistence;
                }

                return (result / maxAmplitude);
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

            void PerlinNoise::populate()
            {
                auto prng = Random::CreatePRNG(Random::PRNG::MersenneTwister);

                int32_t i = 0;
                int32_t j = 0;
                int32_t k = 0;

                for(i = 0; i < B; i++)
                {
                    m_Permutations[i] = i;
                    m_Gradient1[i] = static_cast<float>((prng->next() % B2) - B) * ONE_OVER_B;

                    for(j = 0; j < 2; j++)
                    {
                        m_Gradient2[i][j] = static_cast<float>((prng->next() % B2) - B) * ONE_OVER_B;
                    }

                    normalize2(m_Gradient2[i]);

                    for(j = 0; j < 3; j++)
                    {
                        m_Gradient3[i][j] = static_cast<float>((prng->next() % B2) - B) * ONE_OVER_B;
                    }

                    normalize3(m_Gradient3[i]);
                }

                while(--i)
                {
                    k = m_Permutations[i];
                    m_Permutations[i] = m_Permutations[j = prng->next() % B];
                    m_Permutations[j] = k;
                }

                for(i = 0; i < (B + 2); i++)
                {
                    m_Permutations[B + i] = m_Permutations[i];
		            m_Gradient1[B + i] = m_Gradient1[i];

		            for (j = 0 ; j < 2 ; j++)
                    {
			            m_Gradient2[B + i][j] = m_Gradient2[i][j];
                    }

		            for (j = 0 ; j < 3 ; j++)
                    {
			            m_Gradient3[B + i][j] = m_Gradient3[i][j];
                    }
                }
            }

            float PerlinNoise::getRawNoise(float const x)
            {
                return 0.0f;
            }

            float PerlinNoise::getRawNoise(float const x, float const y)
            {
                int32_t bx0 = 0;
                int32_t bx1 = 0;
                int32_t by0 = 0;
                int32_t by1 = 0;
                int32_t b00 = 0;
                int32_t b10 = 0;
                int32_t b01 = 0;
                int32_t b11 = 0;
                int32_t i   = 0;
                int32_t j   = 0;

                float rx0 = 0.0f;
                float rx1 = 0.0f;
                float ry0 = 0.0f;
                float ry1 = 0.0f;
                float sx  = 0.0f;
                float sy  = 0.0f;
                float a   = 0.0f;
                float b   = 0.0f;
                float t   = 0.0f;
                float u   = 0.0f;
                float v   = 0.0f;

                //--------------------------------------------------------
                // Setup

                t = x + static_cast<float>(N);
                bx0 = static_cast<int32_t>(t) & BM;
                bx1 = (bx0 + 1) % BM;
                rx0 = t - Floor(t);
                rx1 = rx0 - 1.0f;

                t = y + static_cast<float>(N);
                by0 = static_cast<int32_t>(t) & BM;
                by1 = (by0 + 1) % BM;
                ry0 = t - Floor(t);
                ry1 = ry0 - 1.0f;

                //--------------------------------------------------------

                i = m_Permutations[bx0];
                j = m_Permutations[bx1];

                b00 = m_Permutations[i + by0];
                b10 = m_Permutations[j + by0];
                b01 = m_Permutations[i + by1];
                b11 = m_Permutations[j + by1];

                sx = sCurve(rx0);
                sy = sCurve(ry0);

                u = (rx0 * m_Gradient2[b00][0]) + (ry0 * m_Gradient2[b00][1]);
                v = (rx1 * m_Gradient2[b10][0]) + (ry0 * m_Gradient2[b10][1]);
                a = Lerp(sx, u, v);

                u = (rx0 * m_Gradient2[b01][0]) + (ry1 * m_Gradient2[b01][1]);
                v = (rx1 * m_Gradient2[b11][0]) + (ry1 * m_Gradient2[b11][1]);
                b = Lerp(sx, u, v);

                return Lerp(sy, a, b);
            }

            float PerlinNoise::getRawNoise(float const x, float const y, float const z)
            {
                return 0.0f;
            }

            //------------------------------------------------------------------------------
            // PRIVATE METHODS
            //------------------------------------------------------------------------------
        }
    }
}