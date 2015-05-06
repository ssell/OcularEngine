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
#ifndef __H__OCULAR_MATH_RANDOM_ASAMPLER__H__
#define __H__OCULAR_MATH_RANDOM_ASAMPLER__H__

#include "ARandom.hpp"
#include <memory>

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
             * \class ASampler
             *
             * Abstract parent of Psuedo-Random Number Sampling implementations.
             * These algorithms are used to generate pseudo-random numbers that
             * are distributed according to a given probability distribution.
             */
            class ASampler
            {
            public:

                /**
                 * \param[in] source PRNG used to generate interal random values.
                 */
                ASampler(std::shared_ptr<ARandom> const& source);
                ~ASampler();

                /**
                 *  \return Float in the range of [0.0, 1.0]
                 */
                virtual float next() = 0;

            protected:

                std::shared_ptr<ARandom> m_PRNG;

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