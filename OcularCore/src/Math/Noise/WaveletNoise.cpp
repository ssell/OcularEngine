/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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
                m_Scale = 1.0f;

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

            float WaveletNoise::getValue(float const x)
            {
                return getValue(x, 0.0f, 0.0f);
            }

            float WaveletNoise::getValue(float const x, float const y)
            {
                return getValue(x, y, 0.0f);
            }

            float WaveletNoise::getValue(float const x, float const y, float const z)
            {
                return getValue(x, y, z, 0.0f, 0.0f, 0.0f);
            }

            float WaveletNoise::getValue(float const pX, float const pY, float const pZ, float const nX, float const nY, float nZ)
            {
                float result = 0.0f;

                if(m_BandWeights.size() == 0)
                {
                    result = getRawNoise(Vector3f((pX * m_Scale), (pY * m_Scale), (pZ * m_Scale)));
                }
                else
                {
                    float variance = 0.0f;
                    float weight = 0.0f;
                    float q[3] = {0.0f, 0.0f, 0.0f};

                    for(uint32_t band = 0; band < m_BandWeights.size(); band++)
                    {
                        q[0] = 2.0f * (pX * m_Scale) * static_cast<float>(pow(2.0f, band));
                        q[1] = 2.0f * (pY * m_Scale) * static_cast<float>(pow(2.0f, band));
                        q[2] = 2.0f * (pZ * m_Scale) * static_cast<float>(pow(2.0f, band));

                        weight = m_BandWeights[band];
                        result += weight * getRawNoise(Vector3f(q[0], q[1], q[2])); //getRawProjectedNoise(Vector3f(q[0], q[1], q[2]), Vector3f(nX, nY, nZ));
                        variance += (weight * weight);
                    }

                    // Adjust the noise so it has a variance of 1
                    if(variance)
                    {
                        result /= sqrtf(variance * 0.296f);
                    }
                }

                return result;
            }

            void WaveletNoise::setBandWeights(std::vector<float> const& weights)
            {
                m_BandWeights = weights;
            }

            void WaveletNoise::setScale(float const scale)
            {
                m_Scale = scale;
            }

            //------------------------------------------------------------------------------
            // PROTECTED METHODS
            //------------------------------------------------------------------------------

            float WaveletNoise::getRawNoise(Vector3f const& position)
            {
                int32_t i = 0;
                int32_t n = m_Dimensions;
                int32_t f[3] = {0, 0, 0};
                int32_t c[3] = {0, 0, 0};
                int32_t mid[3] = {0, 0, 0};

                float w[3][3] = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}};
                float t = 0.0f;
                float result = 0.0f;

                //---------------------------------------------------
                // Evaluate quadratic B-spline basis functions

                for(i = 0; i < 3; i++)
                {
                    mid[i] = static_cast<int32_t>(ceil(position[i] - 0.5f));
                    t = mid[i] - (position[i] - 0.5f);

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

            float WaveletNoise::getRawProjectedNoise(Vector3f const& position, Vector3f const& normals)
            {
                float result = 0.0f;
                float support = 0.0f;

                int32_t c[3]   = {0, 0, 0};
                int32_t min[3] = {0, 0, 0};
                int32_t max[3] = {0, 0, 0};

                //---------------------------------------------------
                // Bound the support of the basis functions for this projection direction

                for(int32_t i = 0; i < 3; i++)
                {
                    support = (3.0f * (abs(normals[i]))) + (3.0f * sqrt((1.0f - (normals[i] * normals[i])) / 2.0f));
                    min[i]  = static_cast<int32_t>(ceil(position[i] - support));
                    max[i]  = static_cast<int32_t>(ceil(position[i] + support));
                }

                //---------------------------------------------------
                // Loop over the noise coefficients within the bound

                float t      = 0.0f;
                float t1     = 0.0f;
                float t2     = 0.0f;
                float t3     = 0.0f;
                float dot    = 0.0f;
                float weight = 0.0f;

                for(c[2] = min[2]; c[2] <= max[2]; c[2]++)
                {
                    for(c[1] = min[1]; c[1] <= max[1]; c[1]++)
                    {
                        for(c[0] = min[0]; c[0] <= max[0]; c[0]++)
                        {
                            dot = 0.0f;
                            weight = 1.0f;

                            // Dot the normal with the vector from c to p
                            dot += normals[0] * (position[0] - static_cast<float>(c[0]));
                            dot += normals[1] * (position[1] - static_cast<float>(c[1]));
                            dot += normals[2] * (position[2] - static_cast<float>(c[2]));

                            // Evaluate the basis function at c moved halfway to p along the normal
                            for(int32_t i = 0; i < 3; i++)
                            {
                                t  = (static_cast<float>(c[i]) + (normals[i] * dot / 2.0f)) - (position[i] - 1.5f);
                                t1 = t - 1.0f;
                                t2 = 2.0f - t;
                                t3 = 3.0f - t;

                                if((t <= 0.0f) || (t >= 3.0f))
                                {
                                    weight *= 0.0f;
                                }
                                else if(t < 1.0f)
                                {
                                    weight *= t * (t / 2.0f);
                                }
                                else if(t < 2.0f)
                                {
                                    weight *= 1.0f - ((t1 * t1) + (t2 * t2)) / 2.0f;
                                }
                                else 
                                {
                                    weight *= (t3 * t3) / 2.0f;
                                }
                            }

                            // Evaluate the noise by weighting noice coefficients by basis function values
                            result += weight * m_Noise[((mod(c[2], m_Dimensions) * m_Dimensions * m_Dimensions) + (mod(c[1], m_Dimensions) * m_Dimensions) + mod(c[0], m_Dimensions))];
                        }
                    }
                }

                return result;
            }

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