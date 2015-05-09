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
#include "Math/Vector2.hpp"

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
                : ANoise()
            {
                m_Octaves = 6;
                m_Persistence = 0.5f;
                m_Scale = 0.01f;

                m_PRNG = Random::CreatePRNG(Random::MersenneTwister);
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

            void PerlinNoise::seed(int64_t seed)
            {
                m_PRNG->seed(seed);
                populate();
            }

            void PerlinNoise::populate()
            {
                int32_t i = 0;
                int32_t j = 0;
                int32_t temp = 0;

                for( ; i < B; i++)
                {
                    m_Permutations[i] = i;
                    m_Gradient1[i] = getModifiedRandom();
                    
                    for(j = 0; j < 2; j++)
                    {
                        m_Gradient2[i][j] = getModifiedRandom();
                        normalize2(m_Gradient2[i]);
                    }

                    for(j = 0; j < 3; j++)
                    {
                        m_Gradient3[i][j] = getModifiedRandom();
                        normalize3(m_Gradient3[i]);
                    }
                }

                // Shuffle

                for(i = 0; i < B; i++)
                {
                    j = m_PRNG->next(0, BM);

                    temp = m_Permutations[i];
                    m_Permutations[i] = m_Permutations[j];
                    m_Permutations[j] = temp;
                }

                // Essentially duplicate the list in the second halves of the tables

                for(i = 0; i < (B + 2); i++)
                {
                    m_Permutations[B + i] = m_Permutations[i];
                    m_Gradient1[B + i] = m_Gradient1[i];
                    
                    for(j = 0; j < 2; j++)
                    {
                        m_Gradient2[B + i][j] = m_Gradient2[i][j];
                    }
                    
                    for(j = 0; j < 3; j++)
                    {
                        m_Gradient3[B + i][j] = m_Gradient3[i][j];
                    }
                }
            }

            float PerlinNoise::getModifiedRandom()
            {
                return static_cast<float>((m_PRNG->nextSigned() % (B2)) - B) / static_cast<float>(B);
            }

            float PerlinNoise::getRawNoise(float const x)
            {
                return 0.0f;
            }

            float PerlinNoise::getRawNoise(float const x, float const y)
            {
                //--------------------------------------------------------
                // Find the grid points that surround (x,y) and the distance to them.

                /**
                 *  (x0,y1)          (x1,y1)
                 *     *----------------*
                 *     |                |
                 *     |          *     |
                 *     |                |
                 *     |                |
                 *     *----------------*
                 *  (x0,y0)          (x1,y0)
                 */

                int32_t x0 = static_cast<int>(x) % BM;        // Mod 256 so we do not go out of bounds of later arrays
                int32_t x1 = (x0 + 1) % BM;                   
                int32_t y0 = static_cast<int>(y) % BM;
                int32_t y1 = (y0 + 1) % BM;

                float distX0 = x - static_cast<float>(x0);    // Distance to each x0, x1, y0, and y1
                float distX1 = static_cast<float>(x1) - x;
                float distY0 = y - static_cast<float>(y0);
                float distY1 = static_cast<float>(y1) - y; 

                //--------------------------------------------------------
                // Generate indices

                int32_t indexX0 = m_Permutations[x0];
                int32_t indexX1 = m_Permutations[x1];

                int32_t index00 = m_Permutations[indexX0 + y0];
                int32_t index10 = m_Permutations[indexX1 + y0];
                int32_t index01 = m_Permutations[indexX0 + y1];
                int32_t index11 = m_Permutations[indexX1 + y1];

                //--------------------------------------------------------
                // Get the Sigmoid Curves

                float sigmoidX = sigmoidCurve(distX0);
                float sigmoidY = sigmoidCurve(distY0);

                //--------------------------------------------------------
                // Retrieve the pseudo-random gradients (directional vector) for 
                // each corner of the grid. 

                Vector2f lowerLeft(m_Gradient2[index00][0], m_Gradient2[index00][1]);
                Vector2f lowerRight(m_Gradient2[index10][0], m_Gradient2[index10][1]);
                Vector2f upperLeft(m_Gradient2[index01][0], m_Gradient2[index01][1]);
                Vector2f upperRight(m_Gradient2[index11][0], m_Gradient2[index11][1]);

                float s = Vector2f(distX0, distY0).dot(lowerLeft);
                float t = Vector2f(distX1, distY0).dot(lowerRight);
                float u = Vector2f(distX0, distY1).dot(upperLeft);
                float v = Vector2f(distX1, distY1).dot(upperRight);

                // Lerp across the top and bottom x axis

                float a = InterpolateLinear(s, t, sigmoidX);
                float b = InterpolateLinear(u, v, sigmoidX);

                // Lerp across the y axis

                return InterpolateLinear(a, b, sigmoidY);
            }

            float PerlinNoise::getRawNoise(float const x, float const y, float const z)
            {
                return 0.0f;
            }

            void PerlinNoise::getGridInformation(float const& axis, int32_t& grid0, int32_t& grid1, float& dist0, float& dist1)
            {
                float t = axis + N;
                grid0 = (static_cast<int32_t>(t) & BM);
                grid1 = (grid0 + 1) & BM;
                dist0 = t - static_cast<int>(t);
                dist1 = dist0 - 1.0f;
            }

            //------------------------------------------------------------------------------
            // PRIVATE METHODS
            //------------------------------------------------------------------------------
        }
    }
}