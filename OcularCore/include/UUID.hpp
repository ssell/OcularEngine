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
#ifndef __H__OCULAR_CORE_UUID__H__
#define __H__OCULAR_CORE_UUID__H__

#include <cstdint>
#include <string>
#include <boost/uuid/uuid.hpp>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        /**
         * \class UUID
         */
        class UUID
        {
        public:

            UUID();
            ~UUID();

            bool operator==(UUID const& rhs) const;
            bool operator!=(UUID const& rhs) const;

            /**
             * Retrieves an individual octet of the UUID. The UUID
             * is 128 bits in total, or 16 octets.
             *
             * \param[in] index Octet index on range [0,16)
             */
            uint8_t getData(uint32_t const index) const;

            /**
             * Retrieves a string representation of the UUID in the following form:
             *
             *     #-#-#-#
             *
             * Where # is a 32-bit chunk of the UUID data. Example:
             *
             *     131-61-182-198
             */
            std::string toString() const;

            /**
             * Retrieves a 32-bit hash of the string representation of the UUID. Example:
             *
             *     131-61-182-198  ->  1972099726
             */
            uint32_t getHash32() const;

            /**
             * Retrieves a 64-bit hash of the string representation of the UUID. Example:
             *
             *     131-61-182-198  ->  6721546136592699182
             */
            uint64_t getHash64() const;

        protected:

        private:

            boost::uuids::uuid m_UUID;

            uint32_t m_Hash32;
            uint64_t m_Hash64;

            std::string m_String;
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