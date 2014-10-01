/**
* Copyright 2014 Steven T Sell (ssell@ocularinteractive.com)
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

#include "Utilities\Random\XorShift.hpp"

#define SH1 238979280
#define SH2 158852560

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Utils
    {
        namespace Random
        {
            //------------------------------------------------------------------------------
            // CONSTRUCTORS
            //------------------------------------------------------------------------------

            XorShift96::XorShift96()
                : ARandom()
            {
            }

            XorShift96::~XorShift96()
            {

            }

            //------------------------------------------------------------------------------
            // PUBLIC METHODS
            //------------------------------------------------------------------------------

            void XorShift96::seed(long long seed)
            {
                m_X = static_cast<unsigned long>(seed);
                m_Y = m_X + SH1;
                m_Z = m_Y + SH2;
            }

            unsigned XorShift96::next()
            {
                unsigned long t;

                m_X ^= m_X << 16;
                m_X ^= m_X >> 5;
                m_X ^= m_X << 1;

                t = m_X;
                m_X = m_Y;
                m_Y = m_Z;
                m_Z = t ^ m_X ^ m_Y;

                return static_cast<unsigned>(m_Z);
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