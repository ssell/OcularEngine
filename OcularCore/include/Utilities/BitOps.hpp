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
#ifndef __H__OCULAR_UTILITIES_BIT_OPERATIONS__H__
#define __H__OCULAR_UTILITIES_BIT_OPERATIONS__H__

#include <bitset>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Utils
     * @{
     */
    namespace Utils
    {
        /**
         * \addtogroup BitOps
         * @{
         */
        namespace BitOps
        {
           /**
            * Checks if the specified bit is set (= 1). If so, returns TRUE.
            *
            * \param[in] t   The object whose bits should be checked.
            * \param[in] pos The position of the bit to check. If this is equal to or 
            * greater than the total number of bits in t, then FALSE is returned.
            */
            template<typename T>
            bool isBitSet(T const& t, unsigned const pos)
            {
                bool result = false;
                const unsigned tSize = sizeof(T) * 8;

                if(pos < tSize)
                {
                    std::bitset<tSize> tBits(t);
                    result = static_cast<bool>(tBits[pos]);
                }

                return result;
            }
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