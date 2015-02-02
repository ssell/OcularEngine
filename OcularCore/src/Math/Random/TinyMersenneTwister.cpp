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

#include "Math/Random/TinyMersenneTwister.hpp"

#define TINYMT64_MEXP 127
#define TINYMT64_SH0 12
#define TINYMT64_SH1 11
#define TINYMT64_SH8 8
#define TINYMT64_MASK UINT64_C(0x7fffffffffffffff)
#define TINYMT64_MUL (1.0 / 18446744073709551616.0)

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

            TinyMersenneTwister::TinyMersenneTwister()
                : ARandom()
            {
            }

            TinyMersenneTwister::~TinyMersenneTwister()
            {

            }

            //------------------------------------------------------------------------------
            // PUBLIC METHODS
            //------------------------------------------------------------------------------

            unsigned TinyMersenneTwister::next()
            {
                return 0;
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