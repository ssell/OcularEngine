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

#include "Math/Random/MersenneTwister19937.hpp"

static const uint32_t N          = 624;
static const uint32_t M          = 397;
static const uint32_t MATRIX_A   = 0x9908b0dfUL;
static const uint32_t UPPER_MASK = 0x80000000UL;
static const uint32_t LOWER_MASK = 0x7fffffffUL;

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        namespace Random
        {
            //------------------------------------------------------------------------------
            // CONSTRUCTORS
            //------------------------------------------------------------------------------

            MersenneTwister19937::MersenneTwister19937()
                : ARandom()
            {
                m_I = N + 1;
            }

            MersenneTwister19937::~MersenneTwister19937()
            {

            }

            //------------------------------------------------------------------------------
            // PUBLIC METHODS
            //------------------------------------------------------------------------------

            void MersenneTwister19937::seed(int64_t seed)
            {
                m_Seed = seed; 

                uint32_t seedCast = static_cast<uint32_t>(seed);
                m_State[0] = seedCast & 0xffffffffUL;

                for(m_I = 1; m_I < N; m_I++)
                {
                    m_State[m_I]  = (1812433253UL * (m_State[m_I - 1] ^ (m_State[m_I - 1] >> 30)) + m_I); 
                    m_State[m_I] &= 0xffffffffUL;
                }
            }

            uint32_t MersenneTwister19937::next()
            {
                static uint32_t mag01[2] = {0x0UL, MATRIX_A};
                uint32_t y;

                if(m_I >= N)
                {
                    uint32_t kk;

                    if(m_I == (N + 1))
                    {
                        seed(5489UL);
                    }

                    for(kk = 0; kk < (N - M); kk++)
                    {
                        y = (m_State[kk] & UPPER_MASK) | (m_State[kk + 1] & LOWER_MASK);
                        m_State[kk] = m_State[kk + M] ^ (y >> 1) ^ mag01[y & 0x1UL];
                    }

                    for( ; kk < (N - 1); kk++)
                    {
                        y = (m_State[kk] & UPPER_MASK) | (m_State[kk + 1] & LOWER_MASK);
                        m_State[kk] = m_State[kk+(M - N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
                    }

                    y = (m_State[N - 1] & UPPER_MASK) | (m_State[0] & LOWER_MASK);
                    m_State[N - 1] = m_State[M - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];
                    m_I = 0;
                }

                y  = m_State[m_I++];
                y ^= (y >> 11);
                y ^= (y << 7) & 0x9d2c5680UL;
                y ^= (y << 15) & 0xefc60000UL;
                y ^= (y >> 18);

                return y;
            }

            //------------------------------------------------------------------------------
            // PROTECTED METHODS
            //------------------------------------------------------------------------------

            //------------------------------------------------------------------------------
            // PRIVATE METHODS
            //------------------------------------------------------------------------------
        }
    }
}