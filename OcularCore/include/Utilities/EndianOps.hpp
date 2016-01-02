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
#ifndef __H__OCULAR_UTILITIES_ENDIAN_OPERATIONS__H__
#define __H__OCULAR_UTILITIES_ENDIAN_OPERATIONS__H__

#include "Common.hpp"
#include <cstdint>

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
         * \addtogroup EndianOps
         */
        namespace EndianOps
        {
            /**
             * Converts between the specified endianness orders.
             *
             * \param[in] from      Endianness of the incoming value
             * \param[in] to        Endianness to convert the incoming value to.
             * \param[in,out] value Object to convert.
             */
            void convert(Endianness from, Endianness to, int8_t& value);
            
            /**
             * Converts between the specified endianness orders.
             *
             * \param[in] from      Endianness of the incoming value
             * \param[in] to        Endianness to convert the incoming value to.
             * \param[in,out] value Object to convert.
             */
            void convert(Endianness from, Endianness to, int16_t& value);

            /**
             * Converts between the specified endianness orders.
             *
             * \param[in] from      Endianness of the incoming value
             * \param[in] to        Endianness to convert the incoming value to.
             * \param[in,out] value Object to convert.
             */
            void convert(Endianness from, Endianness to, int32_t& value);

            /**
             * Converts between the specified endianness orders.
             *
             * \param[in] from      Endianness of the incoming value
             * \param[in] to        Endianness to convert the incoming value to.
             * \param[in,out] value Object to convert.
             */
            void convert(Endianness from, Endianness to, int64_t& value);

            /**
             * Converts between the specified endianness orders.
             *
             * \param[in] from      Endianness of the incoming value
             * \param[in] to        Endianness to convert the incoming value to.
             * \param[in,out] value Object to convert.
             */
            void convert(Endianness from, Endianness to, uint8_t& value);

            /**
             * Converts between the specified endianness orders.
             *
             * \param[in] from      Endianness of the incoming value
             * \param[in] to        Endianness to convert the incoming value to.
             * \param[in,out] value Object to convert.
             */
            void convert(Endianness from, Endianness to, uint16_t& value);

            /**
             * Converts between the specified endianness orders.
             *
             * \param[in] from      Endianness of the incoming value
             * \param[in] to        Endianness to convert the incoming value to.
             * \param[in,out] value Object to convert.
             */
            void convert(Endianness from, Endianness to, uint32_t& value);

            /**
             * Converts between the specified endianness orders.
             *
             * \param[in] from      Endianness of the incoming value
             * \param[in] to        Endianness to convert the incoming value to.
             * \param[in,out] value Object to convert.
             */
            void convert(Endianness from, Endianness to, uint64_t& value);

            /**
             * Converts between the specified endianness orders.
             *
             * \param[in] from      Endianness of the incoming value
             * \param[in] to        Endianness to convert the incoming value to.
             * \param[in,out] value Object to convert.
             */
            void convert(Endianness from, Endianness to, float& value);

            /**
             * Converts between the specified endianness orders.
             *
             * \param[in] from      Endianness of the incoming value
             * \param[in] to        Endianness to convert the incoming value to.
             * \param[in,out] value Object to convert.
             */
            void convert(Endianness from, Endianness to, double& value);

            //------------------------------------------------------------------------------

            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            void convertToReverse(int8_t& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            void convertToReverse(int16_t& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            void convertToReverse(int32_t& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            void convertToReverse(int64_t& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            void convertToReverse(uint8_t& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            void convertToReverse(uint16_t& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            void convertToReverse(uint32_t& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            void convertToReverse(uint64_t& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             *
             * NOTE, this method is temporarily unavailable:
             *
             * > Support for floating point types was removed from Boost 1.58.0 because there was not enough time to resolve reliability concerns. 
             * > It is expected that floating point support will be available in Boost 1.59.0.
             * > http://www.boost.org/doc/libs/1_58_0/libs/endian/doc/index.html
             *
             * \param[in,out] value
             */
            void convertToReverse(float& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             *
             * NOTE, this method is temporarily unavailable:
             *
             * > Support for floating point types was removed from Boost 1.58.0 because there was not enough time to resolve reliability concerns. 
             * > It is expected that floating point support will be available in Boost 1.59.0.
             * > http://www.boost.org/doc/libs/1_58_0/libs/endian/doc/index.html

             * \param[in,out] value
             */
            void convertToReverse(double& value);
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