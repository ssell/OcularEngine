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

#include "Math/Random/Random.hpp"
#include "Math/Random/CMWC.hpp"
#include "Math/Random/MersenneTwister19937.hpp"
#include "Math/Random/MersenneTwister127.hpp"
#include "Math/Random/WELL.hpp"
#include "Math/Random/XorShift.hpp"

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

            //------------------------------------------------------------------------------
            // PUBLIC METHODS
            //------------------------------------------------------------------------------
            
            std::shared_ptr<ARandom> CreatePRNG(PRNGImplementation prng)
            {
                std::shared_ptr<ARandom> result;

                switch(prng)
                {
                case PRNGImplementation::TinyMersenneTwister:
                    result = std::make_shared<MersenneTwister127>();
                    break;

                case PRNGImplementation::CMWC:
                    result = std::make_shared<CMWC131104>();
                    break;

                case PRNGImplementation::WELL:
                    result = std::make_shared<WELL512>();
                    break;

                case PRNGImplementation::XorShift:
                    result = std::make_shared<XorShift96>();
                    break;

                case PRNGImplementation::MersenneTwister:
                default:
                    result = std::make_shared<MersenneTwister19937>();
                    break;
                }

                return result;
            }

            std::shared_ptr<ARandom> CreatePRNG(PRNGImplementation prng, int64_t seed)
            {
                std::shared_ptr<ARandom> result = CreatePRNG(prng);
                result->seed(seed);

                return result;
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