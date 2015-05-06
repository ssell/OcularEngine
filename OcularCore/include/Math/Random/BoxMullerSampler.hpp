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

#pragma once
#ifndef __H__OCULAR_MATH_RANDOM_BOX_MULLER_SAMPLER__H__
#define __H__OCULAR_MATH_RANDOM_BOX_MULLER_SAMPLER__H__

#include "ASampler.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Math
     * @{
     */
    namespace Math
    {
        /**
         * \addtogroup Random
         * @{
         */
        namespace Random
        {
            /**
             * \class BoxMullerSampler
             *
             * Implementation of the Polar Form of the Box-Muller transform.
             * The transformed values have a Gaussian distribution.
             */
            class BoxMullerSampler : public ASampler
            {
            public:

                /**
                 * \param[in] source PRNG used to generate interal random values.
                 */
                BoxMullerSampler(std::shared_ptr<ARandom> const& source);

                /**
                 * Generates a value using the standard distribution with mean 0 and deviation 1.
                 * \return Float in the range of [0.0, 1.0]
                 */
                virtual float next();

                /**
                 * Generates a value using the specified mean (mu) and deviation (sigma).
                 * \return Float in the range of [0.0, 1.0]
                 */
                float next(float const mu, float const sigma);

            protected:

            private:

            };
        }
        /**
         * @} End of Doxygen Groups
         */
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif