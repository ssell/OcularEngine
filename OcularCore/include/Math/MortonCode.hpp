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
#ifndef __H__OCULAR_ENGINE_MATH_MORTON_CODE__H__
#define __H__OCULAR_ENGINE_MATH_MORTON_CODE__H__

#include "MathCommon.hpp"

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
        class MortonCode
        {
        public:

            /** 
             * Calculates the Morton Code index value from a three-component point.
             * 
             * The values are expected to be in the range of [0,1].
             *
             * \param[in] x
             * \param[in] y
             * \param[in] z
             */
            static uint64_t calculate(float x, float y, float z);

            /**
             * Calculates the Morton Code index value from a three-component integer point.
             *
             * Only the first 21-bits (counting from the right) are used in calculating the Morton Code.
             * This is due to the interleaving of the three integers resulting in a maximum accuracy of
             * (3 * 21 = 63) bits being stored within the resulting 64-bit integer.
             *
             * \param[in] x
             * \param[in] y
             * \param[in] z
             */
            static uint64_t calculate(uint32_t x, uint32_t y, uint32_t z);

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

//------------------------------------------------------------------------------------------

#endif