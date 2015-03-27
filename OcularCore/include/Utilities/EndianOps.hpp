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
#ifndef __H__OCULAR_UTILITIES_ENDIAN_OPERATIONS__H__
#define __H__OCULAR_UTILITIES_ENDIAN_OPERATIONS__H__

#include "Common.hpp"

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
            void convert(Endianness from, Endianness to, char& value);

            /**
             * Converts between the specified endianness orders.
             *
             * \param[in] from      Endianness of the incoming value
             * \param[in] to        Endianness to convert the incoming value to.
             * \param[in,out] value Object to convert.
             */
            void convert(Endianness from, Endianness to, short& value);

            /**
             * Converts between the specified endianness orders.
             *
             * \param[in] from      Endianness of the incoming value
             * \param[in] to        Endianness to convert the incoming value to.
             * \param[in,out] value Object to convert.
             */
            void convert(Endianness from, Endianness to, long& value);

            /**
             * Converts between the specified endianness orders.
             *
             * \param[in] from      Endianness of the incoming value
             * \param[in] to        Endianness to convert the incoming value to.
             * \param[in,out] value Object to convert.
             */
            void convert(Endianness from, Endianness to, long long& value);

            /**
             * Converts between the specified endianness orders.
             *
             * \param[in] from      Endianness of the incoming value
             * \param[in] to        Endianness to convert the incoming value to.
             * \param[in,out] value Object to convert.
             */
            void convert(Endianness from, Endianness to, unsigned char& value);

            /**
             * Converts between the specified endianness orders.
             *
             * \param[in] from      Endianness of the incoming value
             * \param[in] to        Endianness to convert the incoming value to.
             * \param[in,out] value Object to convert.
             */
            void convert(Endianness from, Endianness to, unsigned short& value);

            /**
             * Converts between the specified endianness orders.
             *
             * \param[in] from      Endianness of the incoming value
             * \param[in] to        Endianness to convert the incoming value to.
             * \param[in,out] value Object to convert.
             */
            void convert(Endianness from, Endianness to, unsigned long& value);

            /**
             * Converts between the specified endianness orders.
             *
             * \param[in] from      Endianness of the incoming value
             * \param[in] to        Endianness to convert the incoming value to.
             * \param[in,out] value Object to convert.
             */
            void convert(Endianness from, Endianness to, unsigned long long& value);

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
            void convertToReverse(char& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            void convertToReverse(short& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            void convertToReverse(long& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            void convertToReverse(long long& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            void convertToReverse(unsigned char& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            void convertToReverse(unsigned short& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            void convertToReverse(unsigned long& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            void convertToReverse(unsigned long long& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            void convertToReverse(float& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
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