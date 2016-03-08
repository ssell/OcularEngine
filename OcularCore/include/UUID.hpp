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
#ifndef __H__OCULAR_CORE_UUID__H__
#define __H__OCULAR_CORE_UUID__H__

#include "Utilities/Types.hpp"

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
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        struct UUID_Internal;

        /**
         * \class UUID
         */
        class UUID
        {
        public:

            UUID(std::string const& uuid);
            UUID(UUID const& other);
            UUID();

            ~UUID();

            UUID& operator=(UUID const&);
            bool operator==(UUID const&) const;
            bool operator!=(UUID const&) const;

            //------------------------------------------------------------

            /**
             * Sets the UUID based off of a valid formatted string representation.
             * \param[in] uuid
             */
            void set(std::string const& uuid);

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
             *
             * \note The string representation is precomputed.
             */
            std::string const& toString() const;

            /**
             * Retrieves a 32-bit hash of the string representation of the UUID. Example:
             *
             *     131-61-182-198  ->  1972099726
             *
             * \note The hash is precomputed.
             */
            uint32_t getHash32() const;

            /**
             * Retrieves a 64-bit hash of the string representation of the UUID. Example:
             *
             *     131-61-182-198  ->  6721546136592699182
             *
             * \note The hash is precomputed.
             */
            uint64_t getHash64() const;

        protected:

            UUID_Internal* m_Internal;

            uint32_t m_Hash32;
            uint64_t m_Hash64;

            std::string m_String;

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

OCULAR_REGISTER_TYPE_CUSTOM(Ocular::Core::UUID, "UUID");

//------------------------------------------------------------------------------------------

#endif