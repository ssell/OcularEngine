/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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
#ifndef __H__OCULAR_MATH_RANDOM_CMWC__H__
#define __H__OCULAR_MATH_RANDOM_CMWC__H__

#include "ARandom.hpp"
#include <array>

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
             * \class CMWC131104
             * Implementation of the 131104 periodicity variation of the CMWC (Complementary-Multiply-With-Carry) PRNG using the IRandom interface.
             */
            class CMWC131104 : public ARandom
            {
            public:

                CMWC131104();
                ~CMWC131104();

                virtual void seed(int64_t seed);
                virtual uint32_t next();

            protected:

            private:

                void finishSeed();

                uint32_t  m_SeedCast;
                uint32_t  m_C;
                
                std::array<uint32_t, 4096> m_Q;
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