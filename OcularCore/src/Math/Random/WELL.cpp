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

#include "Math/Random/WELL.hpp"
#include "Math/Random/XorShift.hpp"

#define STATE_SIZE 16

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

            WELL512::WELL512()
                : ARandom()
            {
                m_State = new unsigned long[STATE_SIZE];
                m_Index = 0;
            }

            WELL512::~WELL512()
            {
                if(m_State != nullptr)
                {
                    delete [] m_State;
                }
            }

            //------------------------------------------------------------------------------
            // PUBLIC METHODS
            //------------------------------------------------------------------------------

            void WELL512::seed(int64_t seed)
            {
                XorShift96 prng;
                prng.seed(seed);

                for (unsigned i = 0; i < STATE_SIZE; i++)
                {
                    m_State[i] = prng.next();
                }
            }

            uint32_t WELL512::next()
            {
                uint32_t a, b, c, d;

                a  = m_State[m_Index];
                c  = m_State[(m_Index + 13) & 15];
                b  = a ^ c ^ (a << 16) ^ (c << 15);
                c  = m_State[(m_Index + 9) & 15];
                c ^= (c >> 11);
                a  = m_State[m_Index] = b ^ c;
                d = a ^ ((a << 5) & 0xDA442D20UL);
                m_Index = (m_Index + 15) & 15;
                a = m_State[m_Index];
                m_State[m_Index] = a ^ b ^ d ^ (a << 2) ^ (b << 18) ^ (c << 28);

                return m_State[m_Index];
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