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

#include "Math/Random/BoxMullerSampler.hpp"

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

            BoxMullerSampler::BoxMullerSampler(std::shared_ptr<ARandom> const& source)
                : ASampler(source)
            {
            }

            //------------------------------------------------------------------------------
            // PUBLIC METHODS
            //------------------------------------------------------------------------------

            float BoxMullerSampler::next(float const mu, float const sigma)
            {
                // Sources:
                // http://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
                // https://www.taygeta.com/random/gaussian.html

                float result = 0.0f;
                float x0 = 0.0f;
                float x1 = 0.0f;
                float y0 = 0.0f;
                float w  = 0.0f;

                static bool useLast = false;
                static float y1 = 0.0f;

                // We generate two valid values: y0 and y1. Return y0 this call, and y1 next call.

                if(useLast)
                {
                    result = y1;
                    useLast = false;
                }
                else
                {
                    do 
                    {
                        x0 = (2.0f * m_PRNG->nextf()) - 1.0f;
                        x1 = (2.0f * m_PRNG->nextf()) - 1.0f;
                        w = (x0 * x0) + (x1 * x1);
                    } 
                    while(w >= 1.0f);
                
                    w = sqrtf((-2.0f * log(w)) / w);
                    y0 = x0 * w;
                    y1 = x1 * w;

                    result = y0;
                    useLast = true;
                }

                return (result * sigma) + mu;
            }

            float BoxMullerSampler::next()
            {
                return next(0.0f, 1.0f);
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