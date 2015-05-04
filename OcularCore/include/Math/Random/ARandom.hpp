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
#ifndef __H__OCULAR_MATH_ARANDOM__H__
#define __H__OCULAR_MATH_ARANDOM__H__

#include <cstdint>

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
             * \class ARandom
             */
            class ARandom
            {
            public:

                ARandom();
                ~ARandom();

                /**
                 * Seeds the PRNG with the current epoch time (NS)
                 */
                void seed();

                /**
                 * Seeds the PRNG with the specified seed value.
                 * \param[in] seed
                 */
                virtual void seed(int64_t seed);

                /**
                 * Retrieves the next pseudo-random number (unbounded).
                 */
                virtual uint32_t next() = 0;

                /**
                 * Retrieves the next pseudo-random number and fits it inside of the specified bounds (this is not a clamp)
                 * 
                 * \param[in] min Minimum value for the random number
                 * \param[in] max Maximum value for the random number
                 */
                virtual uint32_t next(uint32_t min, uint32_t max);

                /**
                 * Retrieves the next pseudo-random number as a float in the
                 * the range of [0.0, 1.0]. The precision dictates the, well uh,
                 * precision of the returned value. 
                 *
                 * \param[in] precision
                 */
                virtual float nextf(float const precision = 0.0001f);

                virtual int32_t nextSigned();

                virtual int32_t nextSigned(int32_t min, int32_t max);

            protected:

                int64_t m_Seed;

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