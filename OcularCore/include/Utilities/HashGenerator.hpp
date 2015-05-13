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
#ifndef __H__OCULAR_UTILITIES_HASH_GENERATOR__H__
#define __H__OCULAR_UTILITIES_HASH_GENERATOR__H__

#include <cstdint>
#include <string>

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
         * \class HashGenerator
         *
         * Generates 32 or 64-bit hash values from strings using the FNV-1A algorithm.
         * 
         * Original Source:
         * http://isthe.com/chongo/tech/comp/fnv/
         */
        class HashGenerator
        {
        public:

            HashGenerator();
            ~HashGenerator();

            /**
             * Generates a 32-bit hash value from the specified string.
             *
             * If you want to hash a non-string value (for example a spatial point
             * like in Ocular::Math::Noise::WorleyNoise) you can use Ocular::Utils::StringComposer.
             *
             * \param[in] str
             * \return 32-bit hash value.
             */
            uint32_t getHash32(std::string const& str);

            /**
             * Generates a 64-bit hash value from the specified string.
             *
             * If you want to hash a non-string value (for example a spatial point
             * like in Ocular::Math::Noise::WorleyNoise) you can use Ocular::Utils::StringComposer.
             *
             * \param[in] str
             * \return 64-bit hash value.
             */
            uint64_t getHash64(std::string const& str);

        protected:

        private:

            uint32_t m_LastHash32;
            uint64_t m_LastHash64;
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