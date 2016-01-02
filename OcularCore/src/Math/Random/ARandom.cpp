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

#include "Math/Random/ARandom.hpp"
#include "Math/MathCommon.hpp"
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

            uint32_t ARandom::operator()()
            {
                return next();
            }

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

            float ARandom::nextf(float precision)
            {
                float result = 0.0f;
                precision = Clamp<float>(precision);

                if(!IsZero(precision))
                {
                    uint32_t max = static_cast<uint32_t>(1.0f / precision);
                    uint32_t value = next(0, max);

                    result = static_cast<float>(value) * precision;
                }

                return result;
            }

            float ARandom::nextf(float min, float max, float precision)
            {
                float result = nextf(precision);
                float range = max - min;

                return (min + (result * range));
            }

            int32_t ARandom::nextSigned()
            {
                uint32_t unsignedNext = next();
                return static_cast<int32_t>(unsignedNext - static_cast<uint32_t>(INT32_MAX));
            }

            int32_t ARandom::nextSigned(int32_t min, int32_t max)
            {
                int32_t value = nextSigned();
                return (value % (max - min)) + min;
            }

            uint32_t ARandom::min()
            {
                return 0;
            }

            uint32_t ARandom::max()
            {
                return UINT32_MAX;
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