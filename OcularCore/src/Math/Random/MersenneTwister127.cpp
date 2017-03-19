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

#include "Math/Random/MersenneTwister127.hpp"

static const int64_t  TINYMT64_MEXP = 127LL;
static const int64_t  TINYMT64_SH0  = 12LL;
static const int64_t  TINYMT64_SH1  = 11LL;
static const int64_t  TINYMT64_SH8  = 8LL;
static const uint64_t TINYMT64_MASK = UINT64_C(0x7fffffffffffffff);

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

            MersenneTwister127::MersenneTwister127()
                : ARandom(),
                  m_Mat1(static_cast<int64_t>(4194639680)),
                  m_Mat2(static_cast<int64_t>(4291887092)),
                  m_TMat(static_cast<int64_t>(6399667842752446396))
            {
                m_Status.fill(0);
            }

            MersenneTwister127::~MersenneTwister127()
            {

            }

            //------------------------------------------------------------------------------
            // PUBLIC METHODS
            //------------------------------------------------------------------------------

            void MersenneTwister127::seed(int64_t seed)
            {
                m_Seed = seed;

                m_Status[0] = seed ^ (m_Mat1 << 32);
                m_Status[1] = m_Mat2 ^ m_TMat;

                for(int i = 1; i < 8; i++)
                {
                    m_Status[i & 1] ^= i + TINYMT64_MASK * (m_Status[(i - 1) & 1] ^ (m_Status[(i - 1) & 1] >> 62));
                }

                if(((m_Status[0] & TINYMT64_MASK) == 0) && (m_Status[1] == 0))
                {
                    m_Status[0] = static_cast<int64_t>('T');
                    m_Status[1] = static_cast<int64_t>('M');
                }
            }

            unsigned MersenneTwister127::next()
            {
                unsigned result = 0;

                nextState();
                result = static_cast<unsigned>(temper());

                return result;
            }

            //------------------------------------------------------------------------------
            // PROTECTED METHODS
            //------------------------------------------------------------------------------

            void MersenneTwister127::nextState()
            {
                uint64_t x;

                m_Status[0] &= TINYMT64_MASK;

                x  = m_Status[0] ^ m_Status[1];
                x ^= x << TINYMT64_SH0;
                x ^= x >> 32ULL;
                x ^= x << 32ULL;
                x ^= x << TINYMT64_SH1;

                m_Status[0] = m_Status[1];
                m_Status[1] = static_cast<int64_t>(x);
                
                m_Status[0] ^= -static_cast<int64_t>(x & 1) & m_Mat1;
                m_Status[1] ^= -static_cast<int64_t>(x & 1) & static_cast<int64_t>(static_cast<uint64_t>(m_Mat2) << 32ULL);
            }

            uint64_t MersenneTwister127::temper()
            {
                uint64_t x;

                x  = static_cast<uint64_t>(m_Status[0] + m_Status[1]);
                x ^= static_cast<uint64_t>(m_Status[0] >> TINYMT64_SH8);
                x ^= static_cast<uint64_t>(-static_cast<int64_t>(x & 1) & m_TMat);

                return x;
            }

            //------------------------------------------------------------------------------
            // PRIVATE METHODS
            //------------------------------------------------------------------------------
        }
    }
}