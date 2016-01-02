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
#ifndef __H__OCULAR_MATH_RANDOM_WELL__H__
#define __H__OCULAR_MATH_RANDOM_WELL__H__

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
             * \class WELL512
             *
             * Implementation of the 512 periodicity variation of the WELL (Well Equidistributed Long-Period Linear) PRNG using the IRandom interface.<br/><br/>
             *
             * Original implementation may be found at: http://www.iro.umontreal.ca/~panneton/well/WELL512a.c <br/>
             * Copyright: Francois Panneton, Pierre L'Ecuyer, and Makoto Matsumoto.
             */
            class WELL512 : public ARandom
            {
            public:

                WELL512();
                ~WELL512();

                virtual void seed(int64_t seed);
                virtual unsigned next();

            protected:

            private:

                unsigned m_Index;
                unsigned long * m_State;
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