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

#include "Math/Noise/WaveletNoise.hpp"
#include "Math/MathCommon.hpp"
#include "Math/Random/Random.hpp"
#include "Math/Random/BoxMullerSampler.hpp"

//------------------------------------------------------------------------------------------

static const int32_t ARAD = 16;

int32_t mod(int32_t const x, int32_t const n)
{
    int32_t m = x % n;
    return (m < 0)  ? m + n : m;
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

            WaveletNoise::WaveletNoise(int32_t const dimensions)
                : ANoise()
            {
                m_Dimensions = dimensions;

                // Must be even dimensions
                if(m_Dimensions % 2)
                {
                    m_Dimensions++;
                }

                m_NoiseSize = (m_Dimensions * m_Dimensions * m_Dimensions);
                m_Noise = new float[m_NoiseSize];

                generate();
            }

            WaveletNoise::~WaveletNoise()
            {
                delete [] m_Noise;
                m_Noise = nullptr;
            }

            //------------------------------------------------------------------------------
            // PUBLIC METHODS
            //------------------------------------------------------------------------------

            float WaveletNoise::getValue(float const x, float const y, float const z)
            {
                int32_t i = 0;
                int32_t n = m_Dimensions;
                int32_t f[3] = {0, 0, 0};
                int32_t c[3] = {0, 0, 0};
                int32_t mid[3] = {0, 0, 0};

                float p[3] = {x, y, z};
                float w[3][3] = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}};
                float t = 0.0f;
                float result = 0.0f;

                //---------------------------------------------------
                // Evaluate quadratic B-spline basis functions

                for(i = 0; i < 3; i++)
                {
                    mid[i] = static_cast<int32_t>(ceil(p[i] - 0.5f));
                    t = mid[i] - (p[i] - 0.5f);

                    w[i][0] = t * t / 2.0f;
                    w[i][2] = (1.0f - t) * (1.0f - t) / 2.0f;
                    w[i][1] = 1.0f - w[i][0] - w[i][2];
                }

                //---------------------------------------------------
                // Evaluate noise by weighting noise coefficients by basis function values

                float weight = 1.0f;

                for(f[2] = -1; f[2] <= 1; f[2]++)
                {
                    for(f[1] = -1; f[1] <= 1; f[1]++)
                    {
                        for(f[0] = -1; f[0] <= 1; f[0]++)
                        {
                            weight = 1.0f;

                            for(i = 0; i < 3; i++)
                            {
                                c[i] = mod((mid[i] + f[i]), n);
                                weight *= w[i][f[i] + 1];
                            }

                            result += weight * m_Noise[(c[2] * n * n) + (c[1] * n) + c[0]];
                        }
                    }
                }

                return result;
            }

            //------------------------------------------------------------------------------
            // PROTECTED METHODS
            //------------------------------------------------------------------------------

            void WaveletNoise::generate()
            {
                int32_t x = 0;
                int32_t y = 0;
                int32_t z = 0;
                int32_t i = 0;

                float* temp1 = new float[m_NoiseSize];
                float* temp2 = new float[m_NoiseSize];
                float* noise = new float[m_NoiseSize];

                //---------------------------------------------------
                // Step 1: Fill the tile with random numbers on range [-1.0, 1.0]

                auto prng = Random::CreatePRNG(Random::PRNG::XorShift);

                for(i = 0; i < m_NoiseSize; i++)
                {
                    noise[i] = prng->nextf();
                }

                //---------------------------------------------------
                // Step 2 & 3: Downsample and then Upsample

                for(y = 0; y < m_Dimensions; y++)
                {
                    for(z = 0; z < m_Dimensions; z++)
                    {
                        i = (y * m_Dimensions) + (z * m_Dimensions * m_Dimensions);
                        
                        downsample(&noise[i], &temp1[i], m_Dimensions, 1);
                        upsample(&temp1[i], &temp2[i], m_Dimensions, 1);
                    }
                }

                for(x = 0; x < m_Dimensions; x++)
                {
                    for(z = 0; z < m_Dimensions; z++)
                    {
                        i = x + (z * m_Dimensions * m_Dimensions);

                        downsample(&temp2[i], &temp1[i], m_Dimensions, m_Dimensions);
                        upsample(&temp1[i], &temp2[i], m_Dimensions, m_Dimensions);
                    }
                }

                for(x = 0; x < m_Dimensions; x++)
                {
                    for(y = 0; y < m_Dimensions; y++)
                    {
                        i = x + (y * m_Dimensions);

                        downsample(&temp2[i], &temp1[i], m_Dimensions, (m_Dimensions * m_Dimensions));
                        upsample(&temp1[i], &temp2[i], m_Dimensions, (m_Dimensions * m_Dimensions));
                    }
                }

                //---------------------------------------------------
                // Step 4: Substract out the coarse-scale constribution (original - (downsample upsample))

                for(i = 0; i < m_NoiseSize; i++)
                {   
                    noise[i] -= temp2[i];
                }

                //---------------------------------------------------
                // Step 5: Avoid even/odd variance difference by adding odd-offset version of noise to itself

                int32_t offset = m_Dimensions / 2;

                if((offset % 2) == 0)
                {
                    offset++;
                }

                for(i = 0, x = 0; x < m_Dimensions; x++)
                {
                    for(y = 0; y < m_Dimensions; y++)
                    {
                        for(z = 0; z < m_Dimensions; z++)
                        {
                            temp1[i++] = noise[mod((x + offset), m_Dimensions) + (mod((y + offset), m_Dimensions) * m_Dimensions) +  (mod((z + offset), m_Dimensions) * m_Dimensions * m_Dimensions)];
                        }
                    }
                }

                for(i = 0; i < m_NoiseSize; i++)
                {
                    m_Noise[i] = noise[i] + temp1[i];
                }

                //---------------------------------------------------
                // Clean up allocated resources

                prng = nullptr;
                
                delete [] noise;
                delete [] temp2;
                delete [] temp1;
            }

            void WaveletNoise::downsample(float* from, float* to, int32_t n, int32_t stride)
            {
                float coefficients[2 * ARAD] = 
                {
                     0.000334f, -0.001528f,  0.000410f,  0.003545f, -0.000938f, -0.008233f,  0.002172f,  0.019120f,
                    -0.005040f, -0.044412f,  0.011655f,  0.103311f, -0.025936f, -0.243780f,  0.033979f,  0.655340f,
                     0.655340f,  0.033979f, -0.243780f, -0.025936f,  0.103311f,  0.011655f, -0.044412f, -0.005040f,
                     0.019120f,  0.002172f, -0.008233f, -0.000938f,  0.003546f,  0.000410f, -0.001528f,  0.000334f
                };

                int32_t cindex = 0;
                int32_t tindex = 0;
                int32_t findex = 0;

                for(int32_t i = 0; i < (n / 2); i++)
                {
                    to[i * stride] = 0.0f;

                    for(int32_t j = ((2 * i) - ARAD); j < ((2 * i) + ARAD); j++)
                    {
                        cindex = ARAD + (j - 2 * i);
                        tindex = i * stride;
                        findex = mod(j, n) * stride;

                        to[tindex] += coefficients[cindex] * from[findex];
                    }
                }
            }

            void WaveletNoise::upsample(float* from, float* to, int32_t n, int32_t stride)
            {
                float coefficients[4] =
                {
                    0.25f, 0.75f, 0.75f, 0.25f
                };

                int32_t cindex = 0;
                int32_t tindex = 0;
                int32_t findex = 0;

                for(int32_t i = 0; i < n; i++)
                {
                    tindex = i * stride;
                    to[tindex] = 0.0f;

                    for(int32_t j = (i / 2); j <= ((i / 2) + 1); j++)
                    {
                        cindex = 2 + (i - (2 * j));
                        findex = mod(j, (n / 2)) * stride;

                        to[tindex] += coefficients[cindex] * from[findex];
                    }
                }
            }

            //------------------------------------------------------------------------------
            // PRIVATE METHODS
            //------------------------------------------------------------------------------
        }
    }
}