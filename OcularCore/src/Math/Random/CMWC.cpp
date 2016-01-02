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

#include "Math/Random/CMWC.hpp"

#define M_C 362436UL
#define M_QSIZE 4096
#define PHI 0x9e3779b9

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

            CMWC131104::CMWC131104()
                : ARandom()
            {
                m_Q = new uint32_t[M_QSIZE];
                m_C = M_C;
            }

            CMWC131104::~CMWC131104()
            {
                if(m_Q != nullptr)
                {
                    delete [] m_Q;
                    m_Q = nullptr;
                }
            }

            //------------------------------------------------------------------------------
            // PUBLIC METHODS
            //------------------------------------------------------------------------------

            void CMWC131104::seed(int64_t seed)
            {
                m_SeedCast = static_cast<uint32_t>(seed);

                m_Q[0] = m_SeedCast;
                m_Q[1] = m_SeedCast + PHI;
                m_Q[2] = m_SeedCast + PHI + PHI;

                for (int i = 3; i < M_QSIZE; i++)
                {
                    m_Q[i] = m_Q[i - 3] ^ m_Q[i - 2] ^ PHI ^ i;
                }
            }

            uint32_t CMWC131104::next()
            {
                static uint32_t i = M_QSIZE - 1;
                uint64_t t = 18782LL;

                i      = (i + 1) & 4095;
                t      = (18705ULL * m_Q[i]) + m_C;
                m_C    = t >> 32;
                m_Q[i] = static_cast<uint32_t>(0xfffffffe - t);

                return m_Q[i];
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