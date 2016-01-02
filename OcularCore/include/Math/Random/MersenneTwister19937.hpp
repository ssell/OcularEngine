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

#pragma once
#ifndef __H__OCULAR_MATH_RANDOM_MERSENNE_TWISTER__H__
#define __H__OCULAR_MATH_RANDOM_MERSENNE_TWISTER__H__

#include "ARandom.hpp"

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
             * \class MersenneTwister19937
             *
             * Implementation of the 19937 periodicity variation of the Mersenne Twister PRNG using the IRandom interface.
             *
             * Original implementation may be found at: http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/MT2002/emt19937ar.html
             * Copyright Takuji Nishimura and Makoto Matsumoto
             */
            class MersenneTwister19937 : public ARandom
            {
            public:

                MersenneTwister19937();
                ~MersenneTwister19937();

                virtual void seed(int64_t seed);
                virtual uint32_t next();

            protected:

                uint32_t m_State[624];
                uint32_t m_I;

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