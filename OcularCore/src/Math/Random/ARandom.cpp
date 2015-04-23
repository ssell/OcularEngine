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

#include "Math/Random/ARandom.hpp"
#include "OcularEngine.hpp"

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

            ARandom::ARandom()
            {
                m_Seed = 0;
            }

            ARandom::~ARandom()
            {

            }

            //------------------------------------------------------------------------------
            // PUBLIC METHODS
            //------------------------------------------------------------------------------

            void ARandom::seed()
            {
                seed(OcularEngine.Clock()->getEpochMS());
            }

            void ARandom::seed(int64_t seed)
            {
                m_Seed = seed;
            }

            uint32_t ARandom::next(uint32_t min, uint32_t max)
            {
                // Example:
                //     Min: 100
                //     Max: 1000
                //     Value: 912
                //     Return: (912 % (1000 - 100)) + 100
                //             (912 % 900) + 100
                //             12 + 100
                //             112

                uint32_t value = next();
                return (value % (max - min)) + min;
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