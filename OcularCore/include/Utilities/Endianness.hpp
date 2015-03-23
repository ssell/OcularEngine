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
#ifndef __H__OCULAR_UTILITIES_ENDIANNESS__H__
#define __H__OCULAR_UTILITIES_ENDIANNESS__H__

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
         * \class Endianness
         * \brief Performs endian conversion
         */
        class Endianness
        {
        public:

            Endianness();
            ~Endianness();

            /**
             * Converts from big endian to the native host endian ordering.
             * \param[in,out] value
             */
            static void convertBigToNative(char& value);

            /**
             * Converts from big endian to the native host endian ordering.
             * \param[in,out] value
             */
            static void convertBigToNative(short& value);

            /**
             * Converts from big endian to the native host endian ordering.
             * \param[in,out] value
             */
            static void convertBigToNative(long& value);

            /**
             * Converts from big endian to the native host endian ordering.
             * \param[in,out] value
             */
            static void convertBigToNative(long long& value);

            /**
             * Converts from big endian to the native host endian ordering.
             * \param[in,out] value
             */
            static void convertBigToNative(unsigned char& value);

            /**
             * Converts from big endian to the native host endian ordering.
             * \param[in,out] value
             */
            static void convertBigToNative(unsigned short& value);

            /**
             * Converts from big endian to the native host endian ordering.
             * \param[in,out] value
             */
            static void convertBigToNative(unsigned long& value);

            /**
             * Converts from big endian to the native host endian ordering.
             * \param[in,out] value
             */
            static void convertBigToNative(unsigned long long& value);

            /**
             * Converts from big endian to the native host endian ordering.
             * \param[in,out] value
             */
            static void convertBigToNative(float& value);

            /**
             * Converts from big endian to the native host endian ordering.
             * \param[in,out] value
             */
            static void convertBigToNative(double& value);

            /**
             * Converts from little endian to the native host endian ordering.
             * \param[in,out] value
             */
            static void convertLittleToNative(char& value);

            /**
             * Converts from little endian to the native host endian ordering.
             * \param[in,out] value
             */
            static void convertLittleToNative(short& value);

            /**
             * Converts from little endian to the native host endian ordering.
             * \param[in,out] value
             */
            static void convertLittleToNative(long& value);

            /**
             * Converts from little endian to the native host endian ordering.
             * \param[in,out] value
             */
            static void convertLittleToNative(long long& value);

            /**
             * Converts from little endian to the native host endian ordering.
             * \param[in,out] value
             */
            static void convertLittleToNative(unsigned char& value);

            /**
             * Converts from little endian to the native host endian ordering.
             * \param[in,out] value
             */
            static void convertLittleToNative(unsigned short& value);

            /**
             * Converts from little endian to the native host endian ordering.
             * \param[in,out] value
             */
            static void convertLittleToNative(unsigned long& value);

            /**
             * Converts from little endian to the native host endian ordering.
             * \param[in,out] value
             */
            static void convertLittleToNative(unsigned long long& value);

            /**
             * Converts from little endian to the native host endian ordering.
             * \param[in,out] value
             */
            static void convertLittleToNative(float& value);

            /**
             * Converts from little endian to the native host endian ordering.
             * \param[in,out] value
             */
            static void convertLittleToNative(double& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            static void convertToReverse(char& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            static void convertToReverse(short& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            static void convertToReverse(long& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            static void convertToReverse(long long& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            static void convertToReverse(unsigned char& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            static void convertToReverse(unsigned short& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            static void convertToReverse(unsigned long& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            static void convertToReverse(unsigned long long& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            static void convertToReverse(float& value);
            
            /**
             * Converts from big endian to little endian, and vice versa.
             * \param[in,out] value
             */
            static void convertToReverse(double& value);

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