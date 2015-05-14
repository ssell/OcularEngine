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

#include "UUID.hpp"
#include "OcularEngine.hpp"
#include "Math/MathCommon.hpp"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <sstream>

//------------------------------------------------------------------------------------------

static boost::uuids::random_generator g_UUIDGenerator;

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        UUID::UUID()
        {
            boost::uuids::uuid uuid = g_UUIDGenerator();
            memcpy(m_Data, &uuid, sizeof(uint8_t) * 16);

            std::stringstream sstream;
            sstream << static_cast<uint32_t>(m_Data[0]) << "-"
                    << static_cast<uint32_t>(m_Data[4]) << "-"
                    << static_cast<uint32_t>(m_Data[8]) << "-"
                    << static_cast<uint32_t>(m_Data[12]);

            m_String = sstream.str();
            m_Hash32 = OcularEngine.HashGenerator()->getHash32(m_String);
            m_Hash64 = OcularEngine.HashGenerator()->getHash64(m_String);
        }

        UUID::~UUID()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool UUID::operator==(UUID const& rhs) const
        {
            bool result = true;

            for(uint32_t i = 0; i < 16; i++)
            {
                if(m_Data[i] != rhs.getData(i))
                {
                    result = false;
                    break;
                }
            }

            return result;
        }

        bool UUID::operator!=(UUID const& rhs) const
        {
            return !(*this == rhs);
        }

        uint8_t UUID::getData(uint32_t const index) const
        {
            return m_Data[Math::Clamp<uint32_t>(index, 0, 15)];
        }

        std::string UUID::toString() const
        {
            return m_String;
        }

        uint32_t UUID::getHash32() const
        {
            return m_Hash32;
        }

        uint64_t UUID::getHash64() const
        {
            return m_Hash64;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}